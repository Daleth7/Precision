#include <iterator> // For std::advance()

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            namespace Img{
                template <typename IntType, typename ISIType>
                typename ISIType::str_type str( const IntType& num,
                                                const ISIType& img_set
                ){
                    typedef typename IntType::size_type size_type;
                    typedef typename ISIType::str_type str_type;

                    if(num.is_zero()){
                        return str_type(1, img_set.plus())
                             + str_type(1, img_set.digit(0));
                    }
                    str_type toreturn(num.count_digits() + 1, img_set.digit(0));
                    toreturn[0] = (num.is_positive() ? img_set.plus() : img_set.minus());
                    for(
                        size_type i(1);
                        i <= num.count_digits();
                        ++i
                    ){
                        toreturn[toreturn.size()-i] = img_set.digit(num.digit(i-1));
                    }
                    return toreturn;
                }

                //Set the precision through parameter
                template <typename IntType, typename ISIType>
                typename ISIType::str_type sci_note( const IntType& num,
                                                     typename IntType::size_type prec,
                                                     const ISIType& img_set
                ){
                    typedef typename ISIType::str_type str_type;

                    if(num.is_zero()){
                        return str_type(1, img_set.plus())
                             + str_type(1, img_set.digit(0));
                    }

                    //Display +#E0
                    if(num.count_digits() < 2)
                        return str<IntType, ISIType>(num, img_set)
                                + str_type(1, img_set.exponent())
                                + str_type(1, img_set.digit(0));

                    // Start with the basic stringification of the number
                    str_type toreturn(str<IntType, ISIType>(num, img_set));

                    // Calculate exponent number
                    typename IntType::size_type exp(toreturn.size() - 2);

                    // Insert the point symbol
                    toreturn.insert(2, 1, img_set.point());

                    // Remove glyphs according to specified precision
                    if(prec < exp)
                        toreturn.erase(3+prec);
                    if(toreturn.back() == img_set.point())
                        toreturn.pop_back();

                    // Append the exponent symbol to base
                    toreturn += str_type(1, img_set.exponent());

                    // Convert the exponent number to a string and append
                    str_type exp_str;
                    do{
                        exp_str.insert( exp_str.begin(),
                                        img_set.digit(exp % num.base())
                                        );

                        exp /= num.base();
                    }while(exp > 0);
                    toreturn += exp_str;

                    return toreturn;
                }

                template <typename IntType, typename ISIType>
                typename ISIType::str_type
                    sci_note_w_spaces( const IntType& num,
                                       typename IntType::size_type prec,
                                       const ISIType& img_set
                ){
                    typedef typename ISIType::str_type str_type;

                    str_type toreturn(sci_note<IntType, ISIType>(num, prec, img_set));
                    if(toreturn == str_type(1, img_set.digit(0))) return toreturn;

                    toreturn.insert(1, 1, img_set.space());//Insert space after the sign

                    // Insert spaces befor and after the exponent symbol
                    toreturn.insert(toreturn.find(img_set.exponent()), 1, img_set.space());
                    toreturn.insert(toreturn.find(img_set.exponent())+1, 1, img_set.space());
                    return toreturn;
                }

                template <typename ISIType, typename SearchPolicy>
                struct ___img_oper_helper{
                    using dtype = typename ISIType::digit_type;
                    using itype = typename ISIType::image_type;

                    static dtype get_index(const ISIType& isi, itype img, dtype base);
                };

                template <typename ISIType>
                struct ___img_oper_helper<ISIType, ImgSearchPolicy::Normal>{
                    using dtype = typename ISIType::digit_type;
                    using itype = typename ISIType::image_type;

                    static dtype get_index(const ISIType& isi, itype img, dtype base){
                        return isi.get_index_norm(img, base);
                    }
                };

                template <typename ISIType>
                struct ___img_oper_helper<ISIType, ImgSearchPolicy::Binary>{
                    using dtype = typename ISIType::digit_type;
                    using itype = typename ISIType::image_type;

                    static dtype get_index(const ISIType& isi, itype img, dtype base){
                        return isi.get_index_bin(img, base);
                    }
                };

                template <typename IntType, typename ISIType, typename SearchPolicy = ImgSearchPolicy::Binary>
                void basic_parse( const typename ISIType::str_type& src,
                            typename IntType::diglist_type& new_list,
                            typename IntType::digit_type base,
                            const ISIType& img_set
                ){
                    typedef typename IntType::digit_type digit_type;
                    typedef typename IntType::size_type size_type;
                    new_list.resize(src.size());
                    if(src.size() > 0){
                        auto iter(new_list.begin());
                        size_type i(src.size());
                        while(i-- > 0){
                            digit_type hold = ___img_oper_helper<ISIType, SearchPolicy>
                                            :: get_index(img_set, src[i], base);

                            *iter = (hold == base ? 0 : hold);

                            ++iter;
                        }

                        while(new_list.size() > 1 && new_list.back() == 0)
                            new_list.pop_back();
                    }
                }

                template <typename IntType, typename ISIType, typename SearchPolicy = ImgSearchPolicy::Binary>
                void parse_w_sign( const typename ISIType::str_type& src,
                                   typename IntType::diglist_type& dest,
                                   typename IntType::sign_type& sign_dest,
                                   typename IntType::digit_type base,
                                   const ISIType& img_set
                ){
                    if(src.size() > 0){
                        // Determine the sign, if any
                        typename ISIType::str_type::size_type start_idx =
                            ( (src.front() == img_set.plus()) || (src.front() == img_set.minus()) );
                        sign_dest.assign(-(src.front() == img_set.minus()));

                        basic_parse<IntType, ISIType, SearchPolicy>
                          ( src.substr(start_idx, src.size()),
                            dest, base, img_set
                            );
                    }
                }

                template <typename IntType, typename ISIType, typename SearchPolicy>
                void parse( const typename ISIType::str_type& src,
                                  typename IntType::diglist_type& dest,
                                  typename IntType::sign_type& sign_dest,
                                  typename IntType::digit_type base,
                                  const ISIType& img_set
                ){
                    if(src.size() > 0){
                        // Determine the exponent, if any
                        typename ISIType::str_type::size_type e_idx = src.find(img_set.exponent());

                        parse_w_sign<IntType, ISIType, SearchPolicy>
                          ( src.substr(0, (e_idx == ISIType::str_type::npos) ? src.size() : (e_idx+1)),
                            dest, sign_dest, base, img_set
                            );

                        // Apply the exponent
                        if(e_idx != ISIType::str_type::npos){
                            const typename ISIType::str_type::size_type len = src.size()-e_idx;
                            typename IntType::size_type exp = 0, pow = 1, i = len;
                            for(; i > 0; --i, pow *= base)
                                exp += ___img_oper_helper<ISIType, SearchPolicy>
                                    :: get_index(img_set, src[i-1+e_idx], base) * pow;
                            dest.insert(dest.begin(), exp, 0);
                        }
                    }
                }
            }
        }
    }
}
#include <iterator> // For std::advance()

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            namespace Img{
                template <typename IntType, typename ISIType>
                typename ISIType::str_type str( const IntType& num,
                                                const ISIType& isi
                ){
                    typedef typename IntType::size_type size_type;
                    typedef typename ISIType::str_type str_type;

                    if(num.is_zero()){
                        return str_type(1, isi.plus())
                             + str_type(1, isi.digit(0));
                    }
                    str_type toreturn(num.count_digits() + 1, isi.digit(0));
                    toreturn[0] = (num.is_positive() ? isi.plus() : isi.minus());
                    for(
                        size_type i(1);
                        i <= num.count_digits();
                        ++i
                    ){
                        toreturn[toreturn.size()-i] = isi.digit(num.digit(i-1));
                    }
                    return toreturn;
                }

                //Set the precision through parameter
                template <typename IntType, typename ISIType>
                typename ISIType::str_type sci_note( const IntType& num,
                                                     typename IntType::size_type prec,
                                                     const ISIType& isi
                ){
                    typedef typename ISIType::str_type str_type;

                    if(num.is_zero()){
                        return str_type(1, isi.plus())
                             + str_type(1, isi.digit(0));
                    }

                    //Display +#E0
                    if(num.count_digits() < 2)
                        return str<IntType, ISIType>(num, isi)
                                + str_type(1, isi.exponent())
                                + str_type(1, isi.digit(0));

                    // Start with the basic stringification of the number
                    str_type toreturn(str<IntType, ISIType>(num, isi));

                    // Calculate exponent number
                    typename IntType::size_type exp(toreturn.size() - 2);

                    // Insert the point symbol
                    toreturn.insert(2, 1, isi.point());

                    // Remove glyphs according to specified precision
                    if(prec < exp)
                        toreturn.erase(3+prec);
                    if(toreturn.back() == isi.point())
                        toreturn.pop_back();

                    // Append the exponent symbol to base
                    toreturn += str_type(1, isi.exponent());

                    // Convert the exponent number to a string and append
                    str_type exp_str;
                    do{
                        exp_str.insert( exp_str.begin(),
                                        isi.digit(exp % num.base())
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
                                       const ISIType& isi
                ){
                    typedef typename ISIType::str_type str_type;

                    str_type toreturn(sci_note<IntType, ISIType>(num, prec, isi));
                    if(toreturn == str_type(1, isi.digit(0))) return toreturn;

                    toreturn.insert(1, 1, isi.space());//Insert space after the sign

                    // Insert spaces befor and after the exponent symbol
                    toreturn.insert(toreturn.find(isi.exponent()), 1, isi.space());
                    toreturn.insert(toreturn.find(isi.exponent())+1, 1, isi.space());
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
                                  typename IntType::digstr_type& new_list,
                                  typename IntType::digit_type base,
                                  const ISIType& isi
                ){
                    typedef typename IntType::digit_type digit_type;
                    typedef typename IntType::size_type size_type;
                    new_list.resize(src.size());
                    if(src.size() > 0){
                        auto iter(new_list.begin());
                        size_type i(src.size());
                        while(i-- > 0){
                            digit_type hold = ___img_oper_helper<ISIType, SearchPolicy>
                                            :: get_index(isi, src[i], base);

                            *iter = (hold == base ? 0 : hold);

                            ++iter;
                        }

                        while(new_list.size() > 1 && new_list.back() == 0)
                            new_list.pop_back();
                    }
                }

                template <typename IntType, typename ISIType, typename SearchPolicy = ImgSearchPolicy::Binary>
                void parse_w_sign( const typename ISIType::str_type& src,
                                   typename IntType::digstr_type& dest,
                                   typename IntType::sign_type& sign_dest,
                                   typename IntType::digit_type base,
                                   const ISIType& isi
                ){
                    if(src.size() > 0){
                        // Determine the sign, if any
                        typename ISIType::str_type::size_type start_idx =
                            ( (src.front() == isi.plus()) || (src.front() == isi.minus()) );
                        sign_dest.assign(-(src.front() == isi.minus()));

                        basic_parse<IntType, ISIType, SearchPolicy>
                          ( src.substr(start_idx, src.size()),
                            dest, base, isi
                            );
                    }
                }

                template <typename IntType, typename ISIType, typename SearchPolicy>
                void parse( const typename ISIType::str_type& src,
                                  typename IntType::digstr_type& dest,
                                  typename IntType::sign_type& sign_dest,
                                  typename IntType::digit_type base,
                                  const ISIType& isi
                ){
                    using sz_type = typename ISIType::str_type::size_type;
                    if(src.size() > 0){
                        // Determine the exponent, if any
                        sz_type e_idx = src.find(isi.exponent());

                        parse_w_sign<IntType, ISIType, SearchPolicy>
                          ( src.substr(0, (e_idx == ISIType::str_type::npos) ? src.size() : (e_idx)),
                            dest, sign_dest, base, isi
                            );

                        // Apply the exponent
                        if(e_idx != ISIType::str_type::npos){
                            // Check for negative exponent
                            const sz_type neg_e = src.find(isi.minus(), e_idx);
                            sz_type len = src.size()-e_idx-1;
                            if(neg_e != ISIType::str_type::npos)
                                --len;

                            // Convert the rest of the string to
                            // an exponent number
                            typename IntType::size_type exp = 0, pow = 1, i = len;
                            for(; i > 0; --i, pow *= base)
                                exp += ___img_oper_helper<ISIType, SearchPolicy>
                                    :: get_index(isi, src[src.size()-i], base) * pow;

                            // Add or remove 0's based on exponent
                            if(neg_e == ISIType::str_type::npos)
                                dest.insert(dest.begin(), exp, 0);
                            else{
                                auto end = dest.begin();
                                std::advance(end, exp);
                                dest.erase(dest.begin(), end);
                            }
                        }
                    }
                }
            }
        }
    }
}
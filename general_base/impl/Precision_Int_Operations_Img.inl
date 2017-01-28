#include <iterator> // For std::advance()

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            namespace Img{
                template <typename StrType, typename IntType, typename CharTIterator>
                StrType str( const IntType& num,
                             CharTIterator digs, CharTIterator syms
                ){
                    typedef typename IntType::size_type size_type;
                    if(num.is_zero())
                        return StrType(1, *syms) + StrType(1, *digs);
                    StrType toreturn(num.count_digits() + 1, *digs);
                    CharTIterator s2(syms);
                    std::advance(s2, 1);
                    toreturn[0] = (num.is_positive() ? *syms : *s2);
                    for(
                        size_type i(1);
                        i <= num.count_digits();
                        ++i
                    ){
                        s2 = digs;
                        std::advance(s2, num.digit(i-1));
                        toreturn[toreturn.size()-i] = *s2;
                    }
                    return toreturn;
                }

                //Set the precision through parameter
                template <typename StrType, typename IntType, typename CharTIterator>
                StrType sci_note( const IntType& num,
                                  typename IntType::size_type prec,
                                  CharTIterator digs, CharTIterator syms
                ){
                    if(num.is_zero())
                        return StrType(1, *syms) + StrType(1, *digs);

                    // Move to the exponent symbol
                    CharTIterator s2(syms);
                    std::advance(s2, 3);

                    //Display +#E0
                    if(num.count_digits() < 2)
                        return str<StrType>(num, digs, syms)
                                + StrType(1, *s2) + StrType(1, *digs);

                    // Start with the basic stringification of the number
                    StrType toreturn(str<StrType>(num, digs, syms));

                    // Calculate exponent number
                    typename IntType::size_type exp(toreturn.size() - 2);

                    // Move to and insert the point symbol
                    std::advance(s2, -1);
                    toreturn.insert(2, 1, *s2);

                    // Remove glyphs according to specified precision
                    if(prec < exp)
                        toreturn.erase(3+prec);
                    if(toreturn.back() == *s2)
                        toreturn.pop_back();

                    // Move back to the exponent symbol and append to base
                    std::advance(s2, 1);
                    toreturn += StrType(1, *s2);

                    // Convert the exponent number to a string and append
                    StrType exp_str;
                    do{
                        s2 = digs;
                        std::advance(s2, exp % num.base());
                        exp_str.insert(exp_str.begin(), *s2);

                        exp /= num.base();
                    }while(exp > 0);
                    toreturn += exp_str;

                    return toreturn;
                }

                template <typename StrType, typename IntType, typename CharTIterator>
                StrType sci_note_w_spaces( const IntType& num,
                                           typename IntType::size_type prec,
                                           CharTIterator digs, CharTIterator syms
                ){
                    StrType toreturn(sci_note<StrType>(num, prec, digs, syms));
                    if(toreturn == StrType(1, *digs)) return toreturn;
                    std::advance(syms, 4);
                    toreturn.insert(1, 1, *syms);//Insert space after the sign
                    CharTIterator s2(syms);
                    std::advance(s2, -1);
                    toreturn.insert(toreturn.find(*s2), 1, *syms);
                    toreturn.insert(toreturn.find(*s2)+1, 1, *syms);
                    return toreturn;
                }

                template <typename StrType, typename IntType, typename CharTIterator>
                void parse( const StrType& src,
                            typename IntType::diglist_type& new_list,
                            typename IntType::digit_type base,
                            const CharTIterator dig_glyphs
                ){
                    typedef typename IntType::digit_type digit_type;
                    typedef typename IntType::size_type size_type;
                    new_list.resize(src.size());
                    if(src.size() > 0){
                        auto iter(new_list.begin());
                        size_type i(src.size());
                        while(i-- > 0){
                            CharTIterator ci = dig_glyphs, ci2 = dig_glyphs;
                            std::advance(ci2, base-1);
                            for(
                                digit_type j(0), k(base-1);
                                j <= k;
                                ++j, --k, ++ci, --ci2
                            ){
                                if(src[i] == *ci){
                                    *iter = j;
                                    break;
                                }
                                if(src[i] == *ci2){
                                    *iter = k;
                                    break;
                                }
                            }
                            ++iter;
                        }

                        while(new_list.size() > 1 && new_list.back() == 0)
                            new_list.pop_back();
                    }
                }

                template <typename IntType, typename ISIType>
                typename ISIType::str_type str( const IntType& num,
                                                const ISIType& img_set
                ){
                    typedef typename IntType::size_type size_type;
                    typedef typename ISIType::str_type str_type;

                    if(num.is_zero()){
                        return str_type(1, img_set.plus())
                             + str_type(1, img_set.digit_image(0));
                    }
                    str_type toreturn(num.count_digits() + 1, img_set.digit_image(0));
                    toreturn[0] = (num.is_positive() ? img_set.plus() : img_set.minus());
                    for(
                        size_type i(1);
                        i <= num.count_digits();
                        ++i
                    ){
                        toreturn[toreturn.size()-i] = img_set.digit_image(num.digit(i-1));
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
                        return str<str_type>(num, img_set)
                                + str_type(1, img_set.exponent())
                                + str_type(1, img_set.digit(0));

                    // Start with the basic stringification of the number
                    str_type toreturn(str<str_type>(num, img_set));

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

                    str_type toreturn(sci_note<str_type>(num, prec, digs, syms));
                    if(toreturn == str_type(1, img_set.digit(0))) return toreturn;

                    toreturn.insert(1, 1, img_set.space());//Insert space after the sign

                    // Insert spaces befor and after the exponent symbol
                    toreturn.insert(toreturn.find(img_set.exponent()), 1, img_set.space());
                    toreturn.insert(toreturn.find(img_set.exponent())+1, 1, img_set.space());
                    return toreturn;
                }

                template <typename IntType, typename ISIType, typename SearchPolicy>
                void parse( const typename ISIType::str_type& src,
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
                            digit_type hold = img_set.get_index<SearchPolicy>(src[i], base);

                            *iter = (hold == base ? 0 : hold);

                            ++iter;
                        }

                        while(new_list.size() > 1 && new_list.back() == 0)
                            new_list.pop_back();
                    }
                }
            }
        }
    }
}
#include <algorithm>

namespace Precision{
    namespace Volatile{
        namespace Float_Operations {
            namespace Img{
                template <typename FloatType, typename ISIType>
                typename ISIType::str_type
                    str( const FloatType& ref, typename FloatType::size_type prec,
                         const ISIType& isi
                         )
                {
                    typedef typename ISIType::str_type str_type;
                    typedef typename str_type::size_type size_type;

                    str_type toreturn = sci_note(ref, prec, isi);

                    // If size is 2, string must be "+0".
                    if(toreturn.size() == 2)
                        return toreturn;

                    // Remove power prefix
                    toreturn.erase(toreturn.find(isi.exponent()));

                    // If power is 0, no need to modify anything.
                    if(ref.power() == 0)
                        return toreturn;

                    if(ref.power() < 0){
                        // Insert leading zeros when number is less than 1.

                        // If precision was 0, there would be no point symbol
                        // Therefore, just return a +0 since number < 1
                        if(toreturn.size() == 2){
                            toreturn[0] = isi.plus();
                            toreturn[1] = isi.digit(0);
                            return toreturn;
                        }

                        // Swap point and most significant digit
                        std::swap(toreturn[1], toreturn[2]);

                        // Insert first leading zero
                        toreturn.insert(1, 1, isi.digit(0));

                        // Now insert leading zeros after point symbol
                        toreturn.insert(3, -ref.power()-1, isi.digit(0));
                    }else if (static_cast<size_type>(ref.power()+3) > toreturn.size()){
                        // Insert trailing zeros when power is greater
                        // than the digit count after the point symbol

                        // Remove point symbol
                        toreturn.erase(2, 1);

                        // Append 0's
                        toreturn.append(ref.power()+2-toreturn.size(), isi.digit(0));
                    }else if (static_cast<size_type>(ref.power()+3) == toreturn.size()){
                        // Simply remove the point symbol
                        toreturn.erase(2, 1);
                    }else{
                        // Simply relocate point symbol when power is
                        // positive but less than the digit count
                        // after the point symbol

                        // Remove point symbol
                        toreturn.erase(2, 1);

                        // Re-insert point symbol
                        toreturn.insert(2+ref.power(), 1, isi.point());
                    }

                    return toreturn;
                }

                template <typename FloatType, typename ISIType>
                typename ISIType::str_type
                    sci_note( const FloatType& ref, typename FloatType::size_type prec,
                              const ISIType& isi
                              )
                {
                    typedef typename FloatType::size_type size_type;
                    typedef typename FloatType::signed_size_type ss_type;
                    typedef typename ISIType::str_type str_type;

                    // Return "+0"
                    if(ref.is_zero())
                        return str_type({isi.plus(), isi.digit(0)});

                    // Determine which precision to use
                    size_type pr = (prec < ref.precision()) ? prec : ref.precision();

                    str_type toreturn(pr + 3, isi.digit(0));
                    toreturn[0] = (ref.is_positive() ? isi.plus() : isi.minus());
                    toreturn[2] = isi.point();

                    // Populate digits after the point
                    for(size_type i = 0; i < pr; ++i)
                        toreturn[i+3] = isi.digit(ref.digit(ref.precision()-1-i));

                    if(toreturn.back() == isi.point())
                        toreturn.resize(2);

                    // Populate digit before the point
                    toreturn[1] = isi.digit(ref.digit(ref.precision()));

                    // Add the exponent
                    toreturn.push_back(isi.exponent());
                    ss_type e_cpy = ref.power();

                    if(e_cpy == 0){
                        toreturn.push_back(isi.digit(0));
                        return toreturn;
                    }

                    if(e_cpy < 0){
                        e_cpy *= -1;
                        toreturn.push_back(isi.minus());
                    }

                    // Convert the power number into a string
                    str_type exp_str;
                    while(e_cpy > 0){
                        exp_str.insert( exp_str.begin(),
                                        isi.digit(e_cpy % ref.base())
                                        );

                        e_cpy /= ref.base();
                    }
                    toreturn += exp_str;

                    return toreturn;
                }

                template <typename FloatType, typename ISIType>
                typename ISIType::str_type
                    sci_note_w_spaces( const FloatType& ref,
                                       typename FloatType::size_type prec,
                                       const ISIType& isi
                                       )
                {
                    typedef typename ISIType::str_type str_type;

                    str_type toreturn(sci_note<FloatType, ISIType>(ref, prec, isi));
                    if(toreturn == str_type(1, isi.digit(0))) return toreturn;

                    toreturn.insert(1, 1, isi.space());//Insert space after the sign

                    // Insert spaces before and after the exponent symbol
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

                template < typename FloatType,
                           typename ISIType,
                           typename SearchPolicy
                           >
                void parse( const typename ISIType::str_type& src,
                            typename FloatType::integer_type& dest,
                            typename FloatType::size_type& dest_prec,
                            typename FloatType::signed_size_type& dest_pow,
                            typename FloatType::digit_type base,
                            const ISIType& isi
                            )
                {
                    typedef typename FloatType::signed_size_type ss_type;
                    typedef typename FloatType::size_type size_type;
                    typedef typename ISIType::str_type str_type;
                    typedef typename ISIType::str_type integer_type;

                    size_type ppos = src.find(isi.point()),
                              epos = src.find(isi.exponent())
                              ;
                    // Find out if there is a number sign symbol
                    bool sign_pres = src.front() == isi.plus() || src.front() == isi.minus();

                    if(ppos != str_type::npos){
                        // Copy over string to use in integer construction
                        str_type int_str = src.substr(0, epos);

                        // Remove point symbol
                        int_str.erase(0, ppos);

                        // Now construct integer
                        dest = integer_type( int_str,
                                             isi.digit_list(), isi.symbol_list()
                                             );
                        // Calculate power based on number of digits that were
                        // to the left of the point symbol.
                        dest_pow = ppos - 1 - (sign_pres ? 1 : 0);
                    } else {
                        // Simply construct integer since there was no point symbol
                        dest = integer_type( src.substr(0, epos),
                                             isi.digit_list(), isi.symbol_list()
                                             );
                        // Since this was an integer, match the power to the precision.
                        dest_pow = 0;
                    }

                    // Calculate precision. Trailing zeros should still be present.
                    dest_prec = dest.count_digits()-1;

                    // Extract power if any
                    if(epos != str_type::npos && src.size() > (epos+1)){
                        dest_pow = 0;
                        str_type pow_str = src.substr(epos+1);
                        // Find out if power is negative
                        bool neg = pow_str.front() == isi.minus();
                        size_type stop_pos = neg ? 1 : 0;

                        // Iterate through power string
                        size_type sz = pow_str.size();
                        ss_type factor = 1;
                        while(sz-- > stop_pos){
                            ss_type addend = ___img_oper_helper<ISIType, SearchPolicy>
                                          :: get_index(isi, pow_str[sz], base)
                                          ;
                            // Add value only if the digit is valid
                            if(addend < base)
                                dest_pow += addend*factor;
                            factor *= base;
                        }

                        if(neg) dest_pow *= -1;
                    }
                }
            }
        }
    }
}
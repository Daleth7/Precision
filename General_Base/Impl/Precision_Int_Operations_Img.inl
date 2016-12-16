#include "Math_Shared_Functions.h"
#include "Math_Shared_Helpers.h"
#include "Exception.h"

#include <utility>
#include <algorithm>
#include <iterator>

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            namespace Img{
                template <typename IntType, typename CharTIterator>
                typename IntType::str_type str(
                    const IntType& num,
                    CharTIterator digs, CharTIterator syms
                ){
                    typedef typename IntType::str_type str_type;
                    typedef typename IntType::size_type size_type;
                    if(num.is_zero())
                        return str_type(1, *syms) + str_type(1, *digs);
                    str_type toreturn(num.count_digits() + 1, *digs);
                    CharTIterator s2(syms);
                    std::advance(s2, 1);
                    toreturn[0] = (num.is_positive() ? *syms : *s2);
                    for(
                        size_type i(1);
                        i <= num.count_digits();
                        ++i
                    ){
                        s2 = digs;
                        std::advance(s2, num.digit_10(i-1));
                        toreturn[toreturn.size()-i] = *s2;
                    }
                    return toreturn;
                }

                //Set the precision through parameter
                template <typename IntType, typename CharTIterator>
                typename IntType::str_type sci_note(
                    const IntType& num, typename IntType::size_type prec,
                    CharTIterator digs, CharTIterator syms
                ){
                    typedef typename IntType::str_type str_type;
                    if(num.is_zero())
                        return str_type(1, *syms) + str_type(1, *digs);
                    CharTIterator s2(syms);
                    std::advance(s2, 3);
                    if(num.count_digits() < 2)
                        //Display +#E0
                        return  str(num, digs, syms)
                                + str_type(1, *s2) + str_type(1, *digs);

                    std::advance(s2, -1);
                    str_type toreturn(str(num, digs, syms));
                    typename IntType::size_type exp(toreturn.size() - 2);
                    toreturn.insert(2, 1, *s2);
                    if(prec < exp)
                        toreturn.erase(3+prec);
                    if(toreturn.back() == *s2)
                        toreturn.pop_back();
                    std::advance(s2, 1);
                    toreturn    += str_type(1, *s2)
                                + str(Math::Helper::cast(num, exp), digs, syms)
                                . substr(1);

                    return toreturn;
                }

                template <typename IntType, typename CharTIterator>
                typename IntType::str_type sci_note_w_spaces(
                    const IntType& num, typename IntType::size_type prec,
                    CharTIterator digs, CharTIterator syms
                ){
                    typedef typename IntType::str_type str_type;
                    str_type toreturn(sci_note(num, prec, digs, syms));
                    if(toreturn == str_type(1, *digs)) return toreturn;
                    std::advance(syms, 4);
                    toreturn.insert(1, 1, *syms);//Insert space after the sign
                    CharTIterator s2(syms);
                    std::advance(s2, -1);
                    toreturn.insert(toreturn.find(*s2), 1, *syms);
                    toreturn.insert(toreturn.find(*s2)+1, 1, *syms);
                    return toreturn;
                }

                template <typename IntType, typename CharTIterator>
                void parse(
                    const typename IntType::str_type& src,
                    typename IntType::diglist_type& new_list,
                    typename IntType::sign_type& new_sign,
                    typename IntType::digit_type base,
                    const CharTIterator digs
                ){
                    typedef typename IntType::digit_type digit_type;
                    typedef typename IntType::size_type size_type;
                    new_list.resize(src.size());
                    if(src.size() > 0){
                        auto iter(new_list.begin());
                        size_type i(src.size());
                        while(i-- > 0){
                            CharTIterator ci = digs, ci2 = digs;
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

                        if(new_list.size() == 1 && new_list.front() == 0)
                            new_sign.make_positive();
                    }
                }
            }
        }
    }
}
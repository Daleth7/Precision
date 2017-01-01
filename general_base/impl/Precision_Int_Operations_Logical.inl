#include <utility>  // For std::swap
#include <cmath>    // For std::fmod

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            //Logical Operators
            template <typename IntType>
            void logical_operation(
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& sign1,
                typename IntType::sign_type sign2,
                unsigned short oper, typename IntType::digit_type base
            ){
                using std::swap;
                if(diglist1.size() < diglist2.size()) swap(diglist1, diglist2);
                diglist2.insert( diglist2.end(),
                                 diglist1.size() - diglist2.size(),
                                 0
                                 );
                typedef typename IntType::catalyst_type catalyst_type;
                auto compl_oper = [base](catalyst_type l1)
                    {return std::fmod(base - 1 - l1);};
                auto and_oper = [base](catalyst_type l1, catalyst_type l2)
                    {return std::fmod((l1 * l2), base);};
                auto or_oper = [base, compl_oper, and_oper](catalyst_type l1, catalyst_type l2)
                    {return compl_oper(and_oper(compl_oper(l1), compl_oper(l2)));};
                auto xor_oper = [base](catalyst_type l1, catalyst_type l2)
                    {return std::fmod((l1 + l2), base);};

                for( auto biter(diglist1.begin()), siter(diglist2.begin());
                     siter != diglist2.end();
                     ++biter, ++siter
                ){
                    typename IntType::catalyst_type bld_temp(*biter), sld_temp(*siter);
                    switch(oper){
                        case 1:
                            *biter = and_oper(bld_temp, sld_temp);
                            break;
                        case 2:
                            *biter = or_oper(bld_temp, sld_temp);
                            break;
                        case 3:
                            *biter = xor_oper(bld_temp, sld_temp);
                            break;
                        case 4:
                            *biter = compl_oper(*biter);
                            break;
                        default:
                            throw oper; //Should never happen
                    }
                }
                while(diglist1.size() > 1 && diglist1.back() == 0)
                    diglist1.pop_back();
                switch(oper){
                    case 1:
                        sign1 =
                            1-(sign1.is_negative() & sign2.is_negative())*2;
                        break;
                    case 2:
                        sign1 =
                            1-(sign1.is_negative() | sign2.is_negative())*2;
                        break;
                    case 3:
                        sign1 =
                            1-(sign1.is_negative() ^ sign2.is_negative())*2;
                        break;
                    case 4:
                        sign1.negate();
                        break;
                    default:
                        throw oper; //Should never happen
                }
            }

            template <typename IntType>
            void logical_and(   //res = (a*b)%base
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& sign1,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){
                logical_operation<IntType>( diglist1, diglist2,
                                            sign1, sign2,
                                            1,
                                            base
                                            );
            }

            template <typename IntType>
            void logical_or(    //res = ~(~a & ~b)
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& sign1,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){
                logical_operation<IntType>( diglist1, diglist2,
                                            sign1, sign2,
                                            2,
                                            base
                                            );
            }

            template <typename IntType>
            void logical_xor(   //res = (~((a+b)%base))%base
                typename IntType::diglist_type& diglist1,
                typename IntType::diglist_type diglist2,
                typename IntType::sign_type& sign1,
                typename IntType::sign_type sign2,
                typename IntType::digit_type base
            ){
                logical_operation<IntType>( diglist1, diglist2,
                                            sign1, sign2,
                                            3,
                                            base
                                            );
            }

            template <typename IntType>
            void logical_inversion( //res = Base - 1 - a
                typename IntType::diglist_type& diglist1,
                typename IntType::sign_type& sign1,
                typename IntType::digit_type base
            ){
                logical_operation<IntType>( diglist1, diglist1,
                                            sign1, sign1,
                                            4,
                                            base
                                            );
            }
        }
    }
}
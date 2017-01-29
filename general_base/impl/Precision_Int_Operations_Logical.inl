#include <cmath>    // For std::fmod

#define AND_OPER 0
#define OR_OPER 1
#define XOR_OPER 2
#define COMPL_OPER 3
#define REV_XOR_OPER 4

namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            //Logical Operators
            template <typename IntType>
            void logical_operation( IntType& lhs,
                                    const typename std::remove_const<IntType>::type&
                                       rhs,
                                    unsigned short oper
            ){
                typedef typename IntType::catalyst_type ld;
                typedef typename IntType::size_type size_type;
                typedef typename IntType::digit_type digit_type;

                const digit_type base = lhs.base();

                auto compl_oper = [base](ld l1)
                    {return base - 1 - l1;};
                auto and_oper = [base](ld l1, ld l2)
                    {return std::fmod(l1 * l2, base);};
                // Use De Morgan's to find equivalent for OR operation
                auto or_oper = [base, compl_oper, and_oper](ld l1, ld l2)
                    {return compl_oper(and_oper(compl_oper(l1), compl_oper(l2)));};
                auto xor_oper = [base](ld l1, ld l2)
                    {return std::fmod((l1 + l2), base);};

                size_type max_len = lhs.count_digits();
                if(rhs.count_digits() > max_len) max_len = rhs.count_digits();

                // Perform the logical operation on each digit
                for(size_type i = 0; i < max_len; ++i){
                    ld lhs_dig = (i < lhs.count_digits()) ? lhs.digit(i) : 0,
                       rhs_dig = (i < rhs.count_digits()) ? rhs.digit(i) : 0,
                       new_dig = 0
                       ;

                    switch(oper){
                        case AND_OPER:
                            new_dig = and_oper(lhs_dig, rhs_dig);
                            break;
                        case OR_OPER:
                            new_dig = or_oper(lhs_dig, rhs_dig);
                            break;
                        case XOR_OPER:
                            new_dig = xor_oper(lhs_dig, rhs_dig);
                            break;
                        case COMPL_OPER:
                            new_dig = compl_oper(lhs_dig);
                            break;
                        case REV_XOR_OPER:
                            new_dig = xor_oper(lhs_dig, rhs_dig);
                            for(digit_type i = 1; i < base-1; ++i)
                                new_dig = xor_oper(new_dig, rhs_dig);
                            break;
                        default:
                            throw oper; //Should never happen
                    }

                    // Replace the value or append
                    lhs.force_assign(i, new_dig);
                }

                // Remove excess 0's, which is possible since digits were forced
                Helper::remove_excess_zeros(lhs);

                // Calculate the new sign
                switch(oper){
                    case AND_OPER:
                        lhs.sign( 1-(Helper::is_negative(lhs)
                                  & Helper::is_negative(rhs))*2
                                  );
                        break;
                    case OR_OPER:
                        lhs.sign( 1-(Helper::is_negative(lhs)
                                  | Helper::is_negative(rhs))*2
                                  );
                        break;
                    case XOR_OPER:
                    case REV_XOR_OPER:
                        lhs.sign( 1-(Helper::is_negative(lhs)
                                  ^ Helper::is_negative(rhs))*2
                                  );
                        break;
                    case COMPL_OPER:
                        Helper::negate(lhs);
                        break;
                    default:
                        throw oper; //Should never happen
                }
            }

            template <typename IntType>
            void logical_and_eq( IntType& lhs,
                                 const typename std::remove_const<IntType>::type&
                                    rhs
                                 )
                {logical_operation<IntType>(lhs, rhs, AND_OPER);}

            template <typename IntType>
            void logical_or_eq( IntType& lhs,
                                 const typename std::remove_const<IntType>::type&
                                    rhs
                                 )
                {logical_operation<IntType>(lhs, rhs, OR_OPER);}

            template <typename IntType>
            void logical_xor_eq( IntType& lhs,
                                 const typename std::remove_const<IntType>::type&
                                    rhs
                                 )
                {logical_operation<IntType>(lhs, rhs, XOR_OPER);}

            template <typename IntType>
            void logical_complement_eq(IntType& lhs)
                {logical_operation<IntType>(lhs, lhs, COMPL_OPER);}

            template <typename IntType>
            void logical_rev_xor_eq(IntType& xor_res, const IntType& rhs)
                {logical_operation<IntType>(xor_res, rhs, REV_XOR_OPER);}
        }
    }
}

#undef AND_OPER
#undef OR_OPER
#undef XOR_OPER
#undef COMPL_OPER
#undef REV_XOR_OPER
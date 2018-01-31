#include "Precision_Int_Operations.h"

namespace Precision{
    namespace Convert_Helper{
        template <typename IntType1, typename IntType2>
        IntType2 convert_base_accumulation( const IntType1& lhs,
                                            const IntType2& rhs
        ){
            // To help speed up calculation, store addends in a bucket
            // and calculate the total sum later.
            Volatile::Int_Operations::Arith_Helper::bucket_type<IntType2> bucket;
            IntType2 factor(Helper::make_one_temp(rhs));
            for(typename IntType2::size_type i = 0; i < Helper::int_size(lhs); ++i){
                IntType2 addend(factor);
                Volatile::Int_Operations::multiply_factor(addend, Helper::digit(lhs, i));

                bucket.emplace_back(addend);

                // Shift factor by one digit place based on original base
                Volatile::Int_Operations::multiply_factor(factor, Helper::base(lhs));
            }

            IntType2 toreturn(Helper::make_zero_temp(rhs));
            Volatile::Int_Operations::Arith_Helper::accumulate(toreturn, bucket);

            toreturn.sign(lhs.sign());

            return toreturn;
        }

        template <typename IntType1, typename IntType2>
        IntType2 convert_base_gathering( const IntType1& lhs,
                                         const IntType2& rhs
        ){
            // To help speed up calculation, store addends in a bucket
            // and calculate the total sum later.
            IntType2 factor(Helper::make_one_temp(rhs)),
                     toreturn(Helper::make_zero_temp(rhs))
                     ;
            for(typename IntType2::size_type i = 0; i < Helper::int_size(lhs); ++i){
                IntType2 addend(factor);
                Volatile::Int_Operations::multiply_factor(addend, Helper::digit(lhs, i));

                Volatile::Int_Operations::add(toreturn, addend);

                // Shift factor by one digit place based on original base
                Volatile::Int_Operations::multiply_factor(factor, Helper::base(lhs));
            }

            toreturn.sign(lhs.sign());

            return toreturn;
        }
    }
    template <typename IntType1, typename IntType2>
    IntType2 convert_base(const IntType1& lhs, const IntType2& rhs){
        if(Helper::int_size(lhs) < 2){
            IntType2 toreturn = Helper::make_one_temp(rhs);
            Volatile::Int_Operations::multiply_factor(toreturn, Helper::digit(lhs,0));
            return toreturn;
        }

        // Take an approach similar to what the multiplication algorithm
        // does. Based on the number of digits, choose whether to
        // accumulate addends (faster but stores whole integers and takes
        // up more space) or gather (stores just one integer but is slower).
        // Both algorithms split up the original number into digit sums as
        // represented by the new base and adds them together. This is done
        // since calculating addends by digit may be easier.
        // E.g.
        // Convert 42 from base 10 to base 16:
        //     42 = 40 + 2 in base 10
        // --> 42 = 4*10 + 2*1 in base 10
        // --> 42 = 0x04*0x0A + 0x02*0x01
        // --> 42 = 0x28 + 0x02
        // --> 42 = 0x2A
        if(Helper::int_size(lhs) < Volatile::Int_Operations::Arith_Helper::acc_sw_min)
            return Convert_Helper::convert_base_accumulation(lhs, rhs);
        else
            return Convert_Helper::convert_base_gathering(lhs, rhs);
    }
}
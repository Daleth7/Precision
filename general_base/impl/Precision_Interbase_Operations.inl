#include "Precision_Int_Operations.h"

namespace Precision{
    namespace Convert_Helper{
        template <typename IntType1, typename IntType2>
        IntType2 convert_base_accumulation( const IntType1& orig,
                                            const IntType2& ref
        ){
            // To help speed up calculation, store addends in a bucket
            // and calculate the total sum later.
            Volatile::Int_Operations::Arith_Helper::bucket_type<IntType2> bucket;
            IntType2 factor(Helper::make_one_temp(ref));
            for(typename IntType2::size_type i = 0; i < Helper::int_size(orig); ++i){
                IntType2 addend(factor);
                Volatile::Int_Operations::multiply_factor(addend, Helper::digit(orig, i));

                bucket.emplace_back(addend);

                // Shift factor by one digit place based on original base
                Volatile::Int_Operations::multiply_factor(factor, Helper::base(orig));
            }

            IntType2 toreturn(Helper::make_zero_temp(ref));
            Volatile::Int_Operations::Arith_Helper::accumulate(toreturn, bucket);

            toreturn.sign(orig.sign());

            return toreturn;
        }

        template <typename IntType1, typename IntType2>
        IntType2 convert_base_gathering( const IntType1& orig,
                                         const IntType2& ref
        ){
            // To help speed up calculation, store addends in a bucket
            // and calculate the total sum later.
            IntType2 factor(Helper::make_one_temp(ref)),
                     toreturn(Helper::make_zero_temp(ref))
                     ;
            for(typename IntType2::size_type i = 0; i < Helper::int_size(orig); ++i){
                IntType2 addend(factor);
                Volatile::Int_Operations::multiply_factor(addend, Helper::digit(orig, i));

                Volatile::Int_Operations::add(toreturn, addend);

                // Shift factor by one digit place based on original base
                Volatile::Int_Operations::multiply_factor(factor, Helper::base(orig));
            }

            toreturn.sign(orig.sign());

            return toreturn;
        }
    }

    template <typename IntType2, typename IntType1, typename Digit_Type>
    IntType2 convert_base(const IntType1& orig, Digit_Type base){
        IntType2 ref;
        Helper::match_base_raw(ref, base);
        return convert_base_copy(orig, ref);
    }

    template <typename IntType1, typename IntType2>
    IntType2 convert_base_copy(const IntType1& orig, const IntType2& ref){
        if(Helper::base(orig) == Helper::base(ref)){
            // Simply copy the digits over since
            // digit lists cannot be directly copied
            // without verifying against a default base.
            IntType2 toreturn = Helper::make_one_temp(ref);
            Helper::match_base(toreturn, orig);

            // Count down to force container to allocate all memory
            // on first iteration instead of allocating every few
            // iterations.
            typename IntType1::size_type i = Helper::int_size(orig);
            while(i-- > 0)
                toreturn.force_assign(i, Helper::digit(orig, i));

            toreturn.sign(orig.sign());

            return toreturn;
        }

        if(Helper::int_size(orig) < 2){
            IntType2 toreturn = Helper::make_one_temp(ref);
            Volatile::Int_Operations::multiply_factor(toreturn, Helper::digit(orig,0));
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
        if(Helper::int_size(orig) < Volatile::Int_Operations::Arith_Helper::acc_sw_min)
            return Convert_Helper::convert_base_accumulation(orig, ref);
        else
            return Convert_Helper::convert_base_gathering(orig, ref);
    }
}
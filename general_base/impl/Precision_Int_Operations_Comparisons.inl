namespace Precision{
    namespace Volatile{
        namespace Int_Operations {
            //Comparisons
            template <typename IntType>
            short compare(const IntType& lhs, const IntType& rhs){
                if(&lhs == &rhs)                            return 0;
                else if(lhs.sign() < rhs.sign())            return -1;
                else if(lhs.sign() > rhs.sign())            return 1;
                using list_type = typename IntType::diglist_type;
                const list_type& diglist1(lhs.digit_list()),
                                 diglist2(rhs.digit_list())
                                 ;
                if( lhs.is_negative() &&
                    diglist1.size() > diglist2.size()
                    )                                       return -1;
                else if( lhs.is_negative() &&
                         diglist1.size() < diglist2.size()
                         )                                  return 1;
                return lhs.sign() * compare_lists(diglist1, diglist2);
            }

            template <typename DigListType>
            short compare_lists (const DigListType& d1, const DigListType& d2){
                //Because this is only the digit list, it is assumed
                //  the magnitudes are being compared.
                if(&d1 == &d2)                  return 0;
                if(d1.size() > d2.size())       return 1;
                if(d1.size() < d2.size())       return -1;
                for(
                    auto titer(d1.crbegin()), siter(d2.crbegin());
                    titer != d1.crend();
                    ++titer, ++siter
                ){
                    if(*titer < *siter)         return -1;
                    else if(*titer > *siter)    return  1;
                }
                return 0;
            }

            template <typename DigListType>
            bool is_zero_list(const DigListType& d)
                {return d.size() == 1u && d.front() == 0;}

            template <typename DigListType>
            bool is_one_list(const DigListType& d, bool is_negative)
                {return d.size() == 1u && d.front() == 1 && (!is_negative);}

            template <typename DigListType>
            bool is_neg_one_list(const DigListType& d, bool is_negative)
                {return d.size() == 1u && d.front() == 1 && is_negative;}
        }
    }
}
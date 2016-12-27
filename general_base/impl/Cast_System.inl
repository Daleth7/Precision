/*  Note: There is no conversion taking place
*/

template <typename Is_Fun>      struct cast_fund;
struct cast_same;
template <typename Pre_Base>    struct cast_dyna;
template <typename Is_DAbs>     struct cast_dabs;
template <typename Pre_Cate>    struct cast_help;
template <typename Pre_Cate>    struct cast_int;

    /* Target type is not from the Precision namespace */
template <>
struct cast_fund<std::true_type>{
    template <typename Num_Type1, typename Num_Type2>
    static Num_Type1 oper(const Num_Type1&, const Num_Type2& n){
        return static_cast<Num_Type1>(n);
    }
};

    /* To integral casts */
template <typename Unknown>
struct cast_int{
    template <typename Int_Type1, typename Num_Type2, typename... AddPack>
    static Int_Type1 oper(
        const Int_Type1&, const Num_Type2& n,
        AddPack... addpack
    ){
        return Int_Type1(n, addpack...);
    }
};

template <>
struct cast_int<Tag::Integral>{
    template <typename Int_Type1, typename Int_Type2, typename... AddPack>
    static Int_Type1 oper(
        const Int_Type1&, const Int_Type2& n,
        AddPack... addpack
    ){
        return Int_Type1(n.diglist(), n.sign(), addpack...);
    }
};

template <>
struct cast_int<Tag::Floating_Point>{
    template <typename Int_Type1, typename Flo_Type2, typename... AddPack>
    static Int_Type1 oper(
        const Int_Type1&, const Flo_Type2& n,
        AddPack... addpack
    ){
        return Int_Type1(n.integer(), addpack...);
    }
};

template <>
struct cast_int<Tag::Fraction>{
    template <typename Int_Type1, typename Fra_Type2, typename... AddPack>
    static Int_Type1 oper(
        const Int_Type1&, const Fra_Type2& n,
        AddPack... addpack
    ){
        return Int_Type1(n.integer(), addpack...);
    }
};

    /* To floating casts */
template <typename Is_Integral_Or_Unknown>
struct cast_flo{
    template <typename Flo_Type1, typename Num_Type2, typename... AddPack>
    static Flo_Type1 oper(
        const Flo_Type1&,
        const Num_Type2& n, AddPack... addpack
    ){
        return Flo_Type1(n, addpack...);
    }
};

template <>
struct cast_flo<Tag::Floating_Point>{
    template <typename Flo_Type1, typename Flo_Type2, typename... AddPack>
    static Flo_Type1 oper(
        const Flo_Type1&,
        const Flo_Type2& n, AddPack... addpack
    ){
        const typename Flo_Type1::Integer& sample_int(n.raw_integer());
        return Flo_Type1(sample_int.diglist(), sample_int.sign(), addpack...);
    }
};

template <>
struct cast_flo<Tag::Fraction>{
    template <typename Flo_Type1, typename Fra_Type2, typename... AddPack>
    static Flo_Type1 oper(
        const Flo_Type1& sample,
        const Fra_Type2& n, AddPack... addpack
    ){
        return cast_flo<Tag::Floating_Point>::oper(sample, n.decimal(), addpack...);
    }
};

    /* To fraction casts */
template <typename Not_Fraction>
struct cast_fra{
    template <typename Fra_Type1, typename Num_Type2, typename... AddPack>
    static Fra_Type1 oper(
        const Fra_Type1&,
        const Num_Type2& n, AddPack... addpack
    ){
        return Fra_Type1(n, addpack...);
    }
};

template <>
struct cast_fra<Tag::Fraction>{
    template <typename Fra_Type1, typename Fra_Type2, typename... AddPack>
    static Fra_Type1 oper(
        const Fra_Type1& sample,
        const Fra_Type2& n, AddPack... addpack
    ){
        return Fra_Type1(n.numerator(), n.denominator(), addpack...);
    }
};


    /* Sift out types like integral and floating */
template <>
struct cast_help<Tag::Integral>{
    template <typename Int_Type1, typename Num_Type2, typename... AddPack>
    static Int_Type1 oper(
        const Int_Type1& sample, const Num_Type2& n,
        AddPack... addpack
    ){
        return cast_int<typename Type_Trait::find_base<Num_Type2, PRE_CATE_>::base>
            :: oper(sample, n, addpack...);
    }
};

template <>
struct cast_help<Tag::Floating_Point>{
    template <typename Flo_Type1, typename Num_Type2, typename... AddPack>
    static Flo_Type1 oper(
        const Flo_Type1& sample, const Num_Type2& n,
        AddPack... addpack
    ){
        return cast_flo<typename Type_Trait::find_base<Num_Type2, PRE_CATE_>::base>
            :: oper(sample, n, sample.precision(), addpack...);
    }
};

template <>
struct cast_help<Tag::Fraction>{
    template <typename Fra_Type1, typename Num_Type2, typename... AddPack>
    static Fra_Type1 oper(
        const Fra_Type1& sample, const Num_Type2& n,
        AddPack... addpack
    ){
        return cast_fra<typename Type_Trait::find_base<Num_Type2, PRE_CATE_>::base>
            :: oper(sample, n, sample.precision(), addpack...);
    }
};

    /* Insert arguments based on whether or not the type is dynamic and/or abstract*/
template <>
struct cast_dabs<std::false_type>{
    template <typename Num_Type1, typename Num_Type2, typename Dig_Type>
    static Num_Type1 oper(
        const Num_Type1& sample, const Num_Type2& n,
        Dig_Type new_base
    ){
        return cast_help<typename Type_Trait::find_base<Num_Type1, PRE_CATE_>::base>
            :: oper(sample, n, sample.wrapper(), new_base);
    }
};

template <>
struct cast_dabs<std::true_type>{
    template <typename Num_Type1, typename Num_Type2, typename Dig_Type>
    static Num_Type1 oper(
        const Num_Type1& sample, const Num_Type2& n,
        Dig_Type new_base
    ){
        return cast_help<typename Type_Trait::find_base<Num_Type1, PRE_CATE_>::base>
            :: oper(sample, n, new_base);
    }
};

template <>
struct cast_dyna<Tag::Dynamic>{
    template <typename Num_Type1, typename Num_Type2>
    static Num_Type1 oper(const Num_Type1& sample, const Num_Type2& n){
        return cast_dabs<typename std::is_base_of<Tag::Abstract, Num_Type1>::type>
            :: oper(sample, n, sample.base());
    }
};

template <>
struct cast_dyna<Tag::Static>{
    template <typename Num_Type1, typename Num_Type2>
    static Num_Type1 oper(const Num_Type1& sample, const Num_Type2& n){
        return cast_help<typename Type_Trait::find_base<Num_Type1, PRE_CATE_>::base>
            :: oper(sample, n);
    }
};

    /* Determine if casting is necessary */
struct cast_same{
    template <typename Num_Type>
    static Num_Type oper(const Num_Type&, const Num_Type& n){
        return n;
    }
    template <typename Num_Type1, typename Num_Type2>
    static Num_Type1 oper(const Num_Type1& sample, const Num_Type2& n){
        return cast_dyna<typename Type_Trait::find_base<Num_Type1, PRE_BASE_>::base>
            :: oper(sample, n);
    }
};

template <>
struct cast_fund<std::false_type>{
    template <typename Num_Type1, typename Num_Type2>
    static Num_Type1 oper(const Num_Type1& sample, const Num_Type2& n){
        return cast_same::oper(sample, n);
    }
};

    /* Interface function */
template <typename Num_Type1, typename Num_Type2>
Num_Type1 cast(const Num_Type1& sample, const Num_Type2& n){
    return cast_fund <typename std::is_fundamental<Num_Type1>::type>
        :: oper(sample, n);
}
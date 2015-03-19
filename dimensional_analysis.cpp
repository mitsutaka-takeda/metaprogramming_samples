// The Programming Language C++ 4th Editionの28章。
template <int M, int K, int S>
struct Unit { // 単位を表現する型。
    enum {m = M, kg = K, s = S};
};

template <typename U1, typename U2>
struct UnitPlus { // 型(U1, U2)から型(type = Unit<X,Y,Z>)への関数(metafunction)。
    using type = Unit<U1::m  + U2::m, U1::kg + U2::kg, U1::s  + U2::s>;
};

// 基本的な単位を表現する型。
using M  = Unit<1, 0, 0>;// メートル
using S  = Unit<0, 0, 1>;// 秒

template <typename U> // Unit
struct Quantity { // 量(数値+単位)を表現する型。
    double val;
    explicit Quantity(double v) : val{v} {}
};

template <typename U>
Quantity<U>
operator+(Quantity<U> l, Quantity<U> r) {// 同じ単位Uを持つ量しか足せない。
    return Quantity<U>{l.val+r.val};
}

template <typename U1, typename U2>
auto
operator*(Quantity<U1> l, Quantity<U2> r) {// 違う単位U1,U2の量でもかけ算はできる。
    return Quantity<typename UnitPlus<U1, U2>::type>{l.val*r.val};
}

int main()
{
    const Quantity<M> distanceFromStationToHo{500}, distanceFromHoToLab{200};
    const auto distanceFromStationToLab = distanceFromStationToHo + distanceFromHoToLab;// 700m
    const Quantity<S> timeFromHoToLab{120}; // 2 min
//    const auto wrongUnit = distanceFromStationToHo + timeFromHoToLab;// コンパイル・エラー。
    return 0;
}

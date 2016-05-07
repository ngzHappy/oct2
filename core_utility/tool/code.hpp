template<typename _T_,std::size_t _N_>
inline auto toTupleLick(_T_ (&i)[_N_])->std::array<_T_,_N_>& {
    return reinterpret_cast<std::array<_T_,_N_>&>(i);
}

template<typename _T_,std::size_t _N_>
inline auto toTupleLick(const _T_ (&i)[_N_])->const std::array<const _T_,_N_>& {
    return reinterpret_cast<const std::array<const _T_,_N_>&>(i);
}

template<typename _T_>
inline decltype(auto) toTupleLick(_T_ &&i) {
    return std::forward<_T_>(i);
}

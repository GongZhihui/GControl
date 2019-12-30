//------------------------------------------------------------------------------
/*
    This file is part of gcontrol: https://github.com/gongzhihui/gcontrol
    Copyright (c) 2019 龚志慧.
    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.
    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#pragma once
#include "stdafx.h"
#include <cmath>
#pragma warning(disable: 4244)

namespace GCtrl 
{

template<class T>
class Rect 
{
public:
    using type = T;

    Rect(T x, T y, T width, T height);

    T &x();
    T &y();
    T &width();
    T &height();
    T right();
    T bottom();

    // 转换为CRect, 是否四舍五入
    CRect crect(bool rounding = true);
    operator CRect();

private:
    T x_{ 0.0 };
    T y_{ 0.0 };
    T width_{ 0.0 };
    T height_{ 0.0 };
};

using IRect = Rect<int>;
using DRect = Rect<double>;

template<class T>
inline Rect<T>::Rect(T x, T y, T width, T height)
    : x_{ x }
    , y_{ y }
    , width_{ width }
    , height_{ height }
{
}

template<class T>
inline T & Rect<T>::x()
{
    return x_;
}

template<class T>
inline T & Rect<T>::y()
{
    return y_;
}

template<class T>
inline T & Rect<T>::width()
{
    return width_;
}

template<class T>
inline T & Rect<T>::height()
{
    return height_;
}

template<class T>
inline T Rect<T>::right()
{
    return x_ + width_;
}

template<class T>
inline T Rect<T>::bottom()
{
    return y_ + height_;
}

template<class T>
inline CRect Rect<T>::crect(bool rounding)
{
    if (!std::is_same<T, int>::value) 
    {
        if (rounding) 
        {
            return CRect(std::round(x_),
                std::round(y_),
                std::round(right()),
                std::round(bottom()));
        }
        else
        {
            // 直接丢掉小数点后面的部分
            return CRect(static_cast<int>(x_),
                static_cast<int>(y_),
                static_cast<int>(x_) + static_cast<int>(width_),
                static_cast<int>(y_) + static_cast<int>(height_));
        }
    }
    else 
    {
        return CRect(x_, y_, right(), bottom());
    }
}

template<class T>
inline Rect<T>::operator CRect()
{
    return crect();
}

} //!namespace

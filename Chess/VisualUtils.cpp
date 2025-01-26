#include "VisualUtils.h"

wchar_t VisualUtils::GetPieceRepresentation(Color color, PieceType piece, bool flipColor)
{
    auto symbol = L'\u2653' + 1 + piece + 6 * color;
    if (!flipColor )
    {
        return symbol;
    }
    if (color == Color::BLACK)
    {
        return symbol - 6;
    }
    return symbol + 6;
}

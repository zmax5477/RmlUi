/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2019 Michael R. P. Ragazzon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef ROCKETCORERCSS_H
#define ROCKETCORERCSS_H

namespace Rocket {
namespace Core {

#include "Types.h"

struct LengthPercentageAuto {
	enum Type { Length, Percentage, Auto } type = Length;
	float value = 0;
	LengthPercentageAuto() {}
	LengthPercentageAuto(Type type, float value = 0) : type(type), value(value) {}
};
struct LengthPercentage {
	enum Type { Length, Percentage } type = Length;
	float value = 0;
	LengthPercentage() {}
	LengthPercentage(Type type, float value = 0) : type(type), value(value) {}
};

struct NumberAuto {
	enum Type { Number, Auto } type = Number;
	float value = 0;
	NumberAuto() {}
	NumberAuto(Type type, float value = 0) : type(type), value(value) {}
};


namespace Style
{


enum class Display { None, Block, Inline, InlineBlock };
enum class Position { Static, Relative, Absolute, Fixed };

enum class Float { None, Left, Right };
enum class Clear { None, Left, Right, Both };

struct VerticalAlign {
	enum Type { Baseline, Middle, Sub, Super, TextTop, TextBottom, Top, Bottom, Length } type;
	float value; // For length type
	VerticalAlign(Type type = Baseline) : type(type), value(0) {}
	VerticalAlign(float value) : type(Length), value(value) {}
};


enum class Overflow { Visible, Hidden, Auto, Scroll };

enum class Clip { None = -1, Auto = 0, NumberStart = 1}; // Can contain any positive value as number

enum class Visibility { Visible, Hidden };

enum class FontStyle { Normal, Italic };
enum class FontWeight { Normal, Bold };

enum class TextAlign { Left, Right, Center, Justify };
enum class TextDecoration { None, Underline };
enum class TextTransform { None, Capitalize, Uppercase, Lowercase };
enum class WhiteSpace { Normal, Pre, Nowrap, Prewrap, Preline };

enum class Drag { None, Drag, DragDrop, Block, Clone };
enum class TabIndex { None, Auto };
enum class Focus { None, Auto };
enum class PointerEvents { None, Auto };

enum class OriginX { Left, Center, Right };
enum class OriginY { Top, Center, Bottom };

struct LineHeight {
	float value = 12.f*1.2f; // The computed value (length)
	enum InheritType { Number, Length } inherit_type = Number;
	float inherit_value = 1.2f;
	LineHeight() {}
	LineHeight(float value, InheritType inherit_type, float inherit_value) : value(value), inherit_type(inherit_type), inherit_value(inherit_value) {}
};

// A computed value is a value resolved as far as possible :before: updating layout. See CSS specs for details of each property.
struct ComputedValues
{
	LengthPercentageAuto margin_top, margin_right, margin_bottom, margin_left;
	LengthPercentage padding_top, padding_right, padding_bottom, padding_left;
	float border_top_width = 0, border_right_width = 0, border_bottom_width = 0, border_left_width = 0;
	Colourb border_top_color{ 255, 255, 255 }, border_right_color{ 255, 255, 255 }, border_bottom_color{ 255, 255, 255 }, border_left_color{ 255, 255, 255 };

	Display display = Display::Inline;
	Position position = Position::Static;

	LengthPercentageAuto top{ LengthPercentageAuto::Auto };
	LengthPercentageAuto right{ LengthPercentageAuto::Auto };
	LengthPercentageAuto bottom{ LengthPercentageAuto::Auto };
	LengthPercentageAuto left{ LengthPercentageAuto::Auto };

	Float float_ = Float::None;
	Clear clear = Clear::None;

	NumberAuto z_index = { NumberAuto::Auto };

	LengthPercentageAuto width = { LengthPercentageAuto::Auto };
	LengthPercentage min_width, max_width;
	LengthPercentageAuto height = { LengthPercentageAuto::Auto };
	LengthPercentage min_height, max_height;

	LineHeight line_height;
	VerticalAlign vertical_align;

	Overflow overflow_x = Overflow::Visible, overflow_y = Overflow::Visible;
	Clip clip = Clip::Auto;

	Visibility visibility = Visibility::Visible;

	Colourb background_color = Colourb(255, 255, 255, 0);
	Colourb color = Colourb(255, 255, 255);
	Colourb image_color = Colourb(255, 255, 255);
	float opacity = 1;

	String font_family;
	String font_charset; // empty is same as "U+0020-007E"
	FontStyle font_style = FontStyle::Normal;
	FontWeight font_weight = FontWeight::Normal;
	float font_size = 12.f;

	TextAlign text_align = TextAlign::Left;
	TextDecoration text_decoration = TextDecoration::None;
	TextTransform text_transform = TextTransform::None;
	WhiteSpace white_space = WhiteSpace::Normal;

	String cursor;

	Drag drag = Drag::None;
	TabIndex tab_index = TabIndex::None;
	Focus focus = Focus::Auto;
	float scrollbar_margin = 0;
	PointerEvents pointer_events = PointerEvents::Auto;

	float perspective = 0;
	LengthPercentage perspective_origin_x = { LengthPercentage::Percentage, 50.f };
	LengthPercentage perspective_origin_y = { LengthPercentage::Percentage, 50.f };

	TransformRef transform;
	LengthPercentage transform_origin_x = { LengthPercentage::Percentage, 50.f };
	LengthPercentage transform_origin_y = { LengthPercentage::Percentage, 50.f };
	float transform_origin_z = 0.0f;

	TransitionList transition;
	AnimationList animation;
};
}

// Note: Auto must be manually handled during layout, here it returns zero.
inline float ResolveProperty(LengthPercentageAuto length, float base_value) {
	if (length.type == LengthPercentageAuto::Length)
		return length.value;
	else if (length.type == LengthPercentageAuto::Percentage)
		return length.value * 0.01f * base_value;
	return 0.0f;
}

inline float ResolveProperty(LengthPercentage length, float base_value) {
	if (length.type == LengthPercentage::Length)
		return length.value;
	else if (length.type == LengthPercentage::Percentage)
		return length.value * 0.01f * base_value;
	return 0.0f;
}


using ComputedValues = Style::ComputedValues;

}
}

#endif

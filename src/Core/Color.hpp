/**
 *    ___      _			
 *   / __\___ | | ___  _ __ 
 *  / /  / _ \| |/ _ \| '__|
 * / /__| (_) | | (_) | |   
 * \____/\___/|_|\___/|_|   
 *
 * @file Color.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 09/07/2024
 * @brief Color class
 */

#ifndef __COLOR_HPP
#define __COLOR_HPP

#include <glm/glm.hpp>
#include <map>
#include <string>

namespace Color {
	// Macro pour définir les couleurs en utilisant des valeurs hexadécimales
	#define _c(rgba) glm::vec4(\
		static_cast<float>((rgba >> 24) & 0xFF) / 255, \
		static_cast<float>((rgba >> 16) & 0xFF) / 255, \
		static_cast<float>((rgba >> 8) & 0xFF) / 255, \
		static_cast<float>(rgba & 0xFF) / 255)

	/* Définition de quelques couleurs */

	const glm::vec4 TRANSPARENT			= _c(0x00000000);

	const glm::vec4 ALICE_BLUE			= _c(0xF0F8FFFF);
	const glm::vec4 ANTIQUE_WHITE		= _c(0xFAEBD7FF);
	const glm::vec4 AQUA_MARINE			= _c(0xF7FFD4FF);
	const glm::vec4 AZURE				= _c(0xF0FFFFFF);
	const glm::vec4 BEIGE				= _c(0xF5F5DCFF);
	const glm::vec4 BISQUE				= _c(0xFFE4C4FF);
	const glm::vec4 BLACK				= _c(0x000000FF);
	const glm::vec4 BLANCHED_ALMOND		= _c(0xFFEBCDFF);
	const glm::vec4 BLUE				= _c(0x0000FFFF);
	const glm::vec4 BLUE_ELECTRICAL		= _c(0x0D63FEFF);
	const glm::vec4 BLUE_VIOLET			= _c(0x502AE2FF);
	const glm::vec4 BROWN				= _c(0xA52A2AFF);
	const glm::vec4 BURLY_WOOD			= _c(0xDEB887FF);
	const glm::vec4 CADET_BLUE			= _c(0x5F9EA0FF);
	const glm::vec4 CHARTREUSE			= _c(0x7FFF00FF);
	const glm::vec4 CHOCOLATE			= _c(0xD2691EFF);
	const glm::vec4 COARL				= _c(0xFF7F50FF);
	const glm::vec4 CORN_FLOWER_BLUE	= _c(0x6495EDFF);
	const glm::vec4 CORN_SILK			= _c(0xFFF8DCFF);
	const glm::vec4 CRIMSON				= _c(0xDC1450FF);
	const glm::vec4 CYAN				= _c(0x00FFFFFF);
	const glm::vec4 DARK_BLUE			= _c(0x00008BFF);
	const glm::vec4 DARK_CYAN			= _c(0x008B8BFF);
	const glm::vec4 DARK_GOLDEN_ROD		= _c(0xB8860BFF);
	const glm::vec4 DRAK_GREY			= _c(0xA9A9A9FF);
	const glm::vec4 DARK_GREEN			= _c(0x006400FF);
	const glm::vec4 DARK_KHAKI			= _c(0xADA75BFF);
	const glm::vec4 DARK_MAGENTA		= _c(0x8B008BFF);
	const glm::vec4 DARK_OLIVER_GREEN	= _c(0x455B1FFF);
	const glm::vec4 DARK_ORANGE			= _c(0xE77400FF);
	const glm::vec4 DARK_ORCHILD		= _c(0x9932CCFF);
	const glm::vec4 DARK_PINK			= _c(0xC78D9BFF);
	const glm::vec4 DARK_PURPLE			= _c(0x610094FF);
	const glm::vec4 DARK_RED			= _c(0x8B0000FF);
	const glm::vec4 DARK_SALMON			= _c(0xE9967AFF);
	const glm::vec4 DARK_SEA_GREEN		= _c(0x8FBC8FFF);
	const glm::vec4 DARK_SLATE_BLUE		= _c(0x483D8BFF);
	const glm::vec4 DARK_SLATE_GREY		= _c(0x483D8BFF);
	const glm::vec4 DARK_TURQUOISE		= _c(0x00CED1FF);
	const glm::vec4 DARK_VIOLET			= _c(0x9400D3FF);
	const glm::vec4 DEEP_PINK			= _c(0xFF1493FF);
	const glm::vec4 DEEP_SKY_BLUE		= _c(0x00BFFFFF);
	const glm::vec4 DIM_GRAY			= _c(0x595959FF);
	const glm::vec4 DIM_GREY			= _c(0x696969FF);
	const glm::vec4 DODGER_BLUE1		= _c(0x0060CFFF);
	const glm::vec4 DODGER_BLUE2		= _c(0x1E90FFFF);
	const glm::vec4 DODGER_BLUE3		= _c(0x46B8FFFF);
	const glm::vec4 FIRE_BRICK			= _c(0xB22222FF);
	const glm::vec4 FLORAL_WHITE		= _c(0xFFFAF0FF);
	const glm::vec4 FOREST_GREEN		= _c(0x228B22FF);
	const glm::vec4 FUCHSIA				= _c(0xFF00FFFF);
	const glm::vec4 GAINSBORO			= _c(0xDCDCDCFF);
	const glm::vec4 GHOST_WHITE			= _c(0xF8F8FFFF);
	const glm::vec4 GOLD				= _c(0xFFD700FF);
	const glm::vec4 GOLDEN_ROD			= _c(0xDAA520FF);
	const glm::vec4 GRAY1				= _c(0x707070FF);
	const glm::vec4 GRAY2				= _c(0x808080FF);
	const glm::vec4 GRAY3				= _c(0x919191FF);
	const glm::vec4 GREEN				= _c(0x00FF00FF);
	const glm::vec4 GREEN_YELLOW		= _c(0xADFF2FFF);
	const glm::vec4 HOT_PINK			= _c(0xFF69B4FF);
	const glm::vec4 INDIGO				= _c(0x4B00B2FF);
	const glm::vec4 IVORY				= _c(0xFFFFF0FF);
	const glm::vec4 KHAKI				= _c(0xF0E68CFF);
	const glm::vec4 LAVENDER			= _c(0xE6E6FAFF);
	const glm::vec4 LAWN_GREEN			= _c(0x7CFC00FF);
	const glm::vec4 LIGHT_BLUE			= _c(0xADD8E6FF);
	const glm::vec4 LIGHT_CORAL			= _c(0xF08080FF);
	const glm::vec4 LIGHT_CYAN			= _c(0xE0FFFFFF);
	const glm::vec4 LIGHT_GREEN			= _c(0x90EE90FF);
	const glm::vec4 LIGHT_GRAY1			= _c(0xC6C6C6FF);
	const glm::vec4 LIGHT_GRAY2			= _c(0xD3D3D3FF);
	const glm::vec4 LIGHT_GRAY3			= _c(0xDCDCDCFF);
	const glm::vec4 LIGHT_ORANGE		= _c(0xFFB410FF);
	const glm::vec4 LIGHT_PINK1			= _c(0xFFB6C1FF);
	const glm::vec4 LIGHT_PINK2			= _c(0xFFA9DCFF);
	const glm::vec4 LIGHT_PINK3			= _c(0xFFBFFFFF);
	const glm::vec4 LIGHT_SALMON		= _c(0xFFA07AFF);
	const glm::vec4 LIGHT_SEA_GREEN		= _c(0x20B2AAFF);
	const glm::vec4 LIGHT_SKY_BLUE		= _c(0x87CEFAFF);
	const glm::vec4 LIGHT_SLATE_GRAY	= _c(0x778899FF);
	const glm::vec4 LIGHT_SLATE_GREY	= _c(0x99AABBFF);
	const glm::vec4 LIGHT_STEEL_BLUE	= _c(0xB0C4DEFF);
	const glm::vec4 LIGHT_YELLOW		= _c(0xFFFFE0FF);
	const glm::vec4 LIME				= _c(0xC0FF00FF);
	const glm::vec4 LIME_GREEN			= _c(0x32CD32FF);
	const glm::vec4 LINEN				= _c(0xFAF0E6FF);
	const glm::vec4 MAGENTA				= _c(0xFF00FFFF);
	const glm::vec4 MAROON				= _c(0x800000FF);
	const glm::vec4 MEDIUM_AQUA_MARINE	= _c(0x66CDAAFF);
	const glm::vec4 MEDIUM_BLUE			= _c(0x0000CDFF);
	const glm::vec4 MEDIUM_ORCHID		= _c(0xBA55D3FF);
	const glm::vec4 MEDIUM_PURPLE		= _c(0x9370DBFF);
	const glm::vec4 MEDIUM_SEA_GREEN	= _c(0x3CB371FF);
	const glm::vec4 MEDIUM_SLATE_BLUE	= _c(0x7B68EEFF);
	const glm::vec4 MEDIUM_SPRING_GREEN	= _c(0x00FA9AFF);
	const glm::vec4 MEDIUM_TURQUOISE	= _c(0x48D1CCFF);
	const glm::vec4 MEDIUM_VIOLET_RED	= _c(0xC71585FF);
	const glm::vec4 MIDNIGHT_BLUE		= _c(0x191970FF);
	const glm::vec4 MINT_CREAM			= _c(0xF5FFDFFF);
	const glm::vec4 MISTY_ROSE			= _c(0xFFE4E1FF);
	const glm::vec4 MOCCASIN			= _c(0xFFE4B5FF);
	const glm::vec4 NAVAJO_WHITE		= _c(0xFFDEADFF);
	const glm::vec4 NAVY				= _c(0x000080FF);
	const glm::vec4 OLDLACE				= _c(0xFDF5E6FF);
	const glm::vec4 OLIVE				= _c(0x808000FF);
	const glm::vec4 OLIVE_DRAB			= _c(0x6B8E23FF);
	const glm::vec4 ORANGE				= _c(0xFF6400FF);
	const glm::vec4 ORANGE_JUICE		= _c(0xFFA500FF);
	const glm::vec4 ORANGE_RED			= _c(0xFF4500FF);
	const glm::vec4 ORCHID				= _c(0xDDA0DDFF);
	const glm::vec4 PALE_GOLDEN_ROD		= _c(0xEEE8AAFF);
	const glm::vec4 PALE_GREEN			= _c(0x98FB98FF);
	const glm::vec4 PALE_TURQUOISE		= _c(0xAFEEEEFF);
	const glm::vec4 PALE_VIOLET_RED		= _c(0xDB7093FF);
	const glm::vec4 PAPAYA_WHIP			= _c(0xFFEFD5FF);
	const glm::vec4 PEACH_PUFF			= _c(0xFFDAB9FF);
	const glm::vec4 PERU				= _c(0xCD853FFF);
	const glm::vec4 PINK				= _c(0xFF81CAFF);
	const glm::vec4 PLUM				= _c(0xDDA0DDFF);
	const glm::vec4 POWDER_BLUE			= _c(0xB0E0E6FF);
	const glm::vec4 PURPLE1				= _c(0x9900CCFF);
	const glm::vec4 PURPLE2				= _c(0x66306CFF);
	const glm::vec4 RED					= _c(0xFF0000FF);
	const glm::vec4 ROSY_BROWN			= _c(0xBC8F8FFF);
	const glm::vec4 ROYAL_BLUE			= _c(0x4169E1FF);
	const glm::vec4 SADDLE_BROWN		= _c(0x8B4513FF);
	const glm::vec4 SALMON				= _c(0xFA8072FF);
	const glm::vec4 SANDY_BROWN			= _c(0xF4A460FF);
	const glm::vec4 SEA_GREEN			= _c(0x2E8B57FF);
	const glm::vec4 SEA_SHELL			= _c(0xFFF5EEFF);
	const glm::vec4 SIENNA				= _c(0xA0522DFF);
	const glm::vec4 SKY_BLUE			= _c(0x87CEEBFF);
	const glm::vec4 SLATE_BLUE			= _c(0x4682B4FF);
	const glm::vec4 SLATE_GRAY			= _c(0x7A8A7CFF);
	const glm::vec4 SNOW				= _c(0xFFFAFAFF);
	const glm::vec4 SPRING_GREEN		= _c(0x00FF7FFF);
	const glm::vec4 STEEL_BLUE			= _c(0x4682B4FF);
	const glm::vec4 TAN					= _c(0xD2B48CFF);
	const glm::vec4 TEAL				= _c(0x008080FF);
	const glm::vec4 THISTLE				= _c(0xD8BFD8FF);
	const glm::vec4 TOMATO				= _c(0xFF6347FF);
	const glm::vec4 TURQUOISE			= _c(0x40E0D0FF);
	const glm::vec4 VIOLET				= _c(0xEE82EEFF);
	const glm::vec4 WEAT				= _c(0xF5DEB3FF);
	const glm::vec4 WHITE				= _c(0xFFFFFFFF);
	const glm::vec4 WHITE_SMOKE			= _c(0xF5F5F5FF);
	const glm::vec4 YELLOW				= _c(0xFFFF00FF);
	const glm::vec4 YELLOW_GREEN		= _c(0x9ACD32FF);
	
	const std::map<std::string, glm::vec4> Map = {
		{"TRANSPARENT", _c(0x00000000)},
		{"ALICE_BLUE", _c(0xF0F8FFFF)},
		{"ANTIQUE_WHITE", _c(0xFAEBD7FF)},
		{"AQUA_MARINE", _c(0xF7FFD4FF)},
		{"AZURE", _c(0xF0FFFFFF)},
		{"BEIGE", _c(0xF5F5DCFF)},
		{"BISQUE", _c(0xFFE4C4FF)},
		{"BLACK", _c(0x000000FF)},
		{"BLANCHED_ALMOND", _c(0xFFEBCDFF)},
		{"BLUE", _c(0x0000FFFF)},
		{"BLUE_ELECTRICAL", _c(0x0D63FEFF)},
		{"BLUE_VIOLET", _c(0x502AE2FF)},
		{"BROWN", _c(0xA52A2AFF)},
		{"BURLY_WOOD", _c(0xDEB887FF)},
		{"CADET_BLUE", _c(0x5F9EA0FF)},
		{"CHARTREUSE", _c(0x7FFF00FF)},
		{"CHOCOLATE", _c(0xD2691EFF)},
		{"COARL", _c(0xFF7F50FF)},
		{"CORN_FLOWER_BLUE", _c(0x6495EDFF)},
		{"CORN_SILK", _c(0xFFF8DCFF)},
		{"CRIMSON", _c(0xDC1450FF)},
		{"CYAN", _c(0x00FFFFFF)},
		{"DARK_BLUE", _c(0x00008BFF)},
		{"DARK_CYAN", _c(0x008B8BFF)},
		{"DARK_GOLDEN_ROD", _c(0xB8860BFF)},
		{"DRAK_GREY", _c(0xA9A9A9FF)},
		{"DARK_GREEN", _c(0x006400FF)},
		{"DARK_KHAKI", _c(0xADA75BFF)},
		{"DARK_MAGENTA", _c(0x8B008BFF)},
		{"DARK_OLIVER_GREEN", _c(0x455B1FFF)},
		{"DARK_ORANGE", _c(0xE77400FF)},
		{"DARK_ORCHILD", _c(0x9932CCFF)},
		{"DARK_PINK", _c(0xC78D9BFF)},
		{"DARK_PURPLE", _c(0x610094FF)},
		{"DARK_RED", _c(0x8B0000FF)},
		{"DARK_SALMON", _c(0xE9967AFF)},
		{"DARK_SEA_GREEN", _c(0x8FBC8FFF)},
		{"DARK_SLATE_BLUE", _c(0x483D8BFF)},
		{"DARK_SLATE_GREY", _c(0x483D8BFF)},
		{"DARK_TURQUOISE", _c(0x00CED1FF)},
		{"DARK_VIOLET", _c(0x9400D3FF)},
		{"DEEP_PINK", _c(0xFF1493FF)},
		{"DEEP_SKY_BLUE", _c(0x00BFFFFF)},
		{"DIM_GRAY", _c(0x595959FF)},
		{"DIM_GREY", _c(0x696969FF)},
		{"DODGER_BLUE1", _c(0x0060CFFF)},
		{"DODGER_BLUE2", _c(0x1E90FFFF)},
		{"DODGER_BLUE3", _c(0x46B8FFFF)},
		{"FIRE_BRICK", _c(0xB22222FF)},
		{"FLORAL_WHITE", _c(0xFFFAF0FF)},
		{"FOREST_GREEN", _c(0x228B22FF)},
		{"FUCHSIA", _c(0xFF00FFFF)},
		{"GAINSBORO", _c(0xDCDCDCFF)},
		{"GHOST_WHITE", _c(0xF8F8FFFF)},
		{"GOLD", _c(0xFFD700FF)},
		{"GOLDEN_ROD", _c(0xDAA520FF)},
		{"GRAY1", _c(0x707070FF)},
		{"GRAY2", _c(0x808080FF)},
		{"GRAY3", _c(0x919191FF)},
		{"GREEN", _c(0x00FF00FF)},
		{"GREEN_YELLOW", _c(0xADFF2FFF)},
		{"HOT_PINK", _c(0xFF69B4FF)},
		{"INDIGO", _c(0x4B00B2FF)},
		{"IVORY", _c(0xFFFFF0FF)},
		{"KHAKI", _c(0xF0E68CFF)},
		{"LAVENDER", _c(0xE6E6FAFF)},
		{"LAWN_GREEN", _c(0x7CFC00FF)},
		{"LIGHT_BLUE", _c(0xADD8E6FF)},
		{"LIGHT_CORAL", _c(0xF08080FF)},
		{"LIGHT_CYAN", _c(0xE0FFFFFF)},
		{"LIGHT_GREEN", _c(0x90EE90FF)},
		{"LIGHT_GRAY1", _c(0xC6C6C6FF)},
		{"LIGHT_GRAY2", _c(0xD3D3D3FF)},
		{"LIGHT_GRAY3", _c(0xDCDCDCFF)},
		{"LIGHT_ORANGE", _c(0xFFB410FF)},
		{"LIGHT_PINK1", _c(0xFFB6C1FF)},
		{"LIGHT_PINK2", _c(0xFFA9DCFF)},
		{"LIGHT_PINK3", _c(0xFFBFFFFF)},
		{"LIGHT_SALMON", _c(0xFFA07AFF)},
		{"LIGHT_SEA_GREEN", _c(0x20B2AAFF)},
		{"LIGHT_SKY_BLUE", _c(0x87CEFAFF)},
		{"LIGHT_SLATE_GRAY", _c(0x778899FF)},
		{"LIGHT_SLATE_GREY", _c(0x99AABBFF)},
		{"LIGHT_STEEL_BLUE", _c(0xB0C4DEFF)},
		{"LIGHT_YELLOW", _c(0xFFFFE0FF)},
		{"LIME", _c(0xC0FF00FF)},
		{"LIME_GREEN", _c(0x32CD32FF)},
		{"LINEN", _c(0xFAF0E6FF)},
		{"MAGENTA", _c(0xFF00FFFF)},
		{"MAROON", _c(0x800000FF)},
		{"MEDIUM_AQUA_MARINE", _c(0x66CDAAFF)},
		{"MEDIUM_BLUE", _c(0x0000CDFF)},
		{"MEDIUM_ORCHID", _c(0xBA55D3FF)},
		{"MEDIUM_PURPLE", _c(0x9370DBFF)},
		{"MEDIUM_SEA_GREEN", _c(0x3CB371FF)},
		{"MEDIUM_SLATE_BLUE", _c(0x7B68EEFF)},
		{"MEDIUM_SPRING_GREEN", _c(0x00FA9AFF)},
		{"MEDIUM_TURQUOISE", _c(0x48D1CCFF)},
		{"MEDIUM_VIOLET_RED", _c(0xC71585FF)},
		{"MIDNIGHT_BLUE", _c(0x191970FF)},
		{"MINT_CREAM", _c(0xF5FFDFFF)},
		{"MISTY_ROSE", _c(0xFFE4E1FF)},
		{"MOCCASIN", _c(0xFFE4B5FF)},
		{"NAVAJO_WHITE", _c(0xFFDEADFF)},
		{"NAVY", _c(0x000080FF)},
		{"OLDLACE", _c(0xFDF5E6FF)},
		{"OLIVE", _c(0x808000FF)},
		{"OLIVE_DRAB", _c(0x6B8E23FF)},
		{"ORANGE", _c(0xFF6400FF)},
		{"ORANGE_JUICE", _c(0xFFA500FF)},
		{"ORANGE_RED", _c(0xFF4500FF)},
		{"ORCHID", _c(0xDDA0DDFF)},
		{"PALE_GOLDEN_ROD", _c(0xEEE8AAFF)},
		{"PALE_GREEN", _c(0x98FB98FF)},
		{"PALE_TURQUOISE", _c(0xAFEEEEFF)},
		{"PALE_VIOLET_RED", _c(0xDB7093FF)},
		{"PAPAYA_WHIP", _c(0xFFEFD5FF)},
		{"PEACH_PUFF", _c(0xFFDAB9FF)},
		{"PERU", _c(0xCD853FFF)},
		{"PINK", _c(0xFF81CAFF)},
		{"PLUM", _c(0xDDA0DDFF)},
		{"POWDER_BLUE", _c(0xB0E0E6FF)},
		{"PURPLE1", _c(0x9900CCFF)},
		{"PURPLE2", _c(0x66306CFF)},
		{"RED", _c(0xFF0000FF)},
		{"ROSY_BROWN", _c(0xBC8F8FFF)},
		{"ROYAL_BLUE", _c(0x4169E1FF)},
		{"SADDLE_BROWN", _c(0x8B4513FF)},
		{"SALMON", _c(0xFA8072FF)},
		{"SANDY_BROWN", _c(0xF4A460FF)},
		{"SEA_GREEN", _c(0x2E8B57FF)},
		{"SEA_SHELL", _c(0xFFF5EEFF)},
		{"SIENNA", _c(0xA0522DFF)},
		{"SKY_BLUE", _c(0x87CEEBFF)},
		{"SLATE_BLUE", _c(0x4682B4FF)},
		{"SLATE_GRAY", _c(0x7A8A7CFF)},
		{"SNOW", _c(0xFFFAFAFF)},
		{"SPRING_GREEN", _c(0x00FF7FFF)},
		{"STEEL_BLUE", _c(0x4682B4FF)},
		{"TAN", _c(0xD2B48CFF)},
		{"TEAL", _c(0x008080FF)},
		{"THISTLE", _c(0xD8BFD8FF)},
		{"TOMATO", _c(0xFF6347FF)},
		{"TURQUOISE", _c(0x40E0D0FF)},
		{"VIOLET", _c(0xEE82EEFF)},
		{"WEAT", _c(0xF5DEB3FF)},
		{"WHITE", _c(0xFFFFFFFF)},
		{"WHITE_SMOKE", _c(0xF5F5F5FF)},
		{"YELLOW", _c(0xFFFF00FF)},
		{"YELLOW_GREEN", _c(0x9ACD32FF)},
	};
} // namespace Color

#endif // __COLOR_HPP

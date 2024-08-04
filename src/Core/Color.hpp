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

namespace Color {
	// Macro pour définir les couleurs en utilisant des valeurs hexadécimales
	#define _c(r, g, b, a) glm::vec4(\
		static_cast<float>(0x##r) / 255, \
		static_cast<float>(0x##g) / 255, \
		static_cast<float>(0x##b) / 255, \
		static_cast<float>(0x##a) / 255)

	/* Définition de quelques couleurs */

	const glm::vec4 TRANSPARENT		   = _c(00,00,00,00);

	const glm::vec4 ALICE_BLUE			= _c(F0,F8,FF,FF);
	const glm::vec4 ANTIQUE_WHITE		= _c(FA,EB,D7,FF);
	const glm::vec4 AQUA_MARINE			= _c(F7,FF,D4,FF);
	const glm::vec4 AZURE				= _c(F0,FF,FF,FF);
	const glm::vec4 BEIGE				= _c(F5,F5,DC,FF);
	const glm::vec4 BISQUE				= _c(FF,E4,C4,FF);
	const glm::vec4 BLACK				= _c(00,00,00,FF);
	const glm::vec4 BLUE				= _c(00,00,FF,FF);
	const glm::vec4 BLUE_VIOLET			= _c(50,2A,E2,FF);
	const glm::vec4 BROWN				= _c(A5,2A,2A,FF);
	const glm::vec4 BURLY_WOOD			= _c(DE,B8,87,FF);
	const glm::vec4 CADET_BLUE			= _c(5F,9E,A0,FF);
	const glm::vec4 CHARTREUSE			= _c(7F,FF,00,FF);
	const glm::vec4 CHOCOLATE			= _c(D2,69,1E,FF);
	const glm::vec4 COARL				= _c(FF,7F,50,FF);
	const glm::vec4 CORN_FLOWER_BLUE	= _c(64,95,ED,FF);
	const glm::vec4 CORN_SILK			= _c(FF,F8,DC,FF);
	const glm::vec4 CRIMSON				= _c(DC,14,50,FF);
	const glm::vec4 CYAN				= _c(00,FF,FF,FF);
	const glm::vec4 DARK_BLUE			= _c(00,00,8B,FF);
	const glm::vec4 DARK_CYAN			= _c(00,8B,8B,FF);
	const glm::vec4 DARK_GOLDEN_ROD		= _c(B8,86,0B,FF);
	const glm::vec4 DARK_GRAY1			= _c(30,30,30,FF);
	const glm::vec4 DARK_GRAY2			= _c(40,40,40,FF);
	const glm::vec4 DARK_GRAY3			= _c(50,50,50,FF);
	const glm::vec4 DARK_GREEN			= _c(00,64,00,FF);
	const glm::vec4 DARK_KAKI			= _c(AD,A7,5B,FF);
	const glm::vec4 DARK_MAGENTA		= _c(8B,00,8B,FF);
	const glm::vec4 DARK_OLiVER_GREEN	= _c(45,5B,1F,FF);
	const glm::vec4 DARK_ORANGE			= _c(E7,74,00,FF);
	const glm::vec4 DARK_ORCHILD		= _c(99,32,CC,FF);
	const glm::vec4 DARK_PINK			= _c(C7,8D,9B,FF);
	const glm::vec4 DARK_PURPLE			= _c(61,00,94,FF);
	const glm::vec4 DARK_RED			= _c(8B,00,00,FF);
	const glm::vec4 DARK_SALMON			= _c(E9,96,7A,FF);
	const glm::vec4 DARK_SEA_GREEN		= _c(8F,BC,8F,FF);
	const glm::vec4 DARK_SLATE_BLUE		= _c(48,3D,8B,FF);
	const glm::vec4 DODGER_BLUE1		= _c(00,60,CF,FF);
	const glm::vec4 DODGER_BLUE2		= _c(1E,90,FF,FF);
	const glm::vec4 DODGER_BLUE3		= _c(46,B8,FF,FF);
	const glm::vec4 FIRE_BRICK			= _c(B2,22,22,FF);
	const glm::vec4 FLORAL_WHITE		= _c(FF,FA,F0,FF);
	const glm::vec4 FOREST_GREEN		= _c(22,8B,22,FF);
	const glm::vec4 GOLD				= _c(FF,D7,00,FF);
	const glm::vec4 GOLD_ROD			= _c(DA,A5,20,FF);
	const glm::vec4 GRAY1				= _c(70,70,70,FF);
	const glm::vec4 GRAY2				= _c(80,80,80,FF);
	const glm::vec4 GRAY3				= _c(90,90,90,FF);
	const glm::vec4 GREEN				= _c(00,FF,00,FF);
	const glm::vec4 GREEN_YELLOW		= _c(AD,FF,2F,FF);
	const glm::vec4 HOT_PINK			= _c(FF,69,B4,FF);
	const glm::vec4 INDIGO				= _c(4B,00,B2,FF);
	const glm::vec4 IVORY				= _c(FF,FF,F0,FF);
	const glm::vec4 KHAKI				= _c(F0,E6,8C,FF);
	const glm::vec4 LAVENDER			= _c(E6,E6,FA,FF);
	const glm::vec4 LAWN_GREEN			= _c(7C,FC,00,FF);
	const glm::vec4 LIGHT_BLUE			= _c(AD,D8,E6,FF);
	const glm::vec4 LIGHT_CORAL			= _c(F0,80,80,FF);
	const glm::vec4 LIGHT_CYAN			= _c(E0,FF,FF,FF);
	const glm::vec4 LIGHT_GREEN			= _c(90,EE,90,FF);
	const glm::vec4 LIGHT_GRAY1			= _c(C6,C6,C6,FF);
	const glm::vec4 LIGHT_GRAY2			= _c(D3,D3,D3,FF);
	const glm::vec4 LIGHT_GRAY3			= _c(DC,DC,DC,FF);
	const glm::vec4 LIGHT_ORANGE		= _c(FF,B4,10,FF);
	const glm::vec4 LIGHT_PINK1			= _c(FF,B6,C1,FF);
	const glm::vec4 LIGHT_PINK2			= _c(FF,A9,DC,FF);
	const glm::vec4 LIGHT_PINK3			= _c(FF,BF,FF,FF);
	const glm::vec4 LIGHT_SALMON		= _c(FF,A0,7A,FF);
	const glm::vec4 LIGHT_YELLOW		= _c(FF,D9,A6,FF);
	const glm::vec4 LIME_GREEN			= _c(32,CD,32,FF);
	const glm::vec4 MAGENTA				= _c(FF,00,FF,FF);
	const glm::vec4 MAROON				= _c(80,00,00,FF);
	const glm::vec4 MEDIUM_AQUA_MARINE	= _c(66,CD,AA,FF);
	const glm::vec4 MEDIUM_SLATE_BLUE	= _c(7B,68,EE,FF);
	const glm::vec4 ORANGE				= _c(FF,64,00,FF);
	const glm::vec4 ORANGE_JUICE		= _c(FF,A5,00,FF);
	const glm::vec4 ORANGE_RED			= _c(FF,45,00,FF);
	const glm::vec4 PERU				= _c(CD,85,3F,FF);
	const glm::vec4 PINK				= _c(FF,81,CA,FF);
	const glm::vec4 PURPLE1				= _c(99,00,CC,FF);
	const glm::vec4 PURPLE2				= _c(66,30,6C,FF);
	const glm::vec4 RED					= _c(FF,00,00,FF);
	const glm::vec4 SIENNA				= _c(A0,52,2D,FF);
	const glm::vec4 SKY_BLUE			= _c(87,CE,EB,FF);
	const glm::vec4 SLATE_BLUE			= _c(46,82,B4,FF);
	const glm::vec4 SLATE_GRAY			= _c(7A,8A,7C,FF);
	const glm::vec4 TURQUOISE			= _c(40,E0,D0,FF);
	const glm::vec4 VIOLET				= _c(EE,82,EE,FF);
	const glm::vec4 WEAT				= _c(F5,DE,B3,FF);
	const glm::vec4 WHITE				= _c(FF,FF,FF,FF);
	const glm::vec4 WHITE_SMOKE			= _c(F5,F5,F5,FF);
	const glm::vec4 YELLOW				= _c(FF,FF,00,FF);
	const glm::vec4 YELLOW_GREEN		= _c(9A,CD,32,FF);

};

#endif // __COLOR_HPP
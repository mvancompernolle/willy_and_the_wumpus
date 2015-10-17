#include "../includes/Rules.h"
#include "../includes/ResourceManager.h"
#include "../includes/ServiceLocator.h"
#include <fstream>
#include <iostream>


Rules::Rules( GLuint w, GLuint h )
	: tbRules(glm::vec2(w * 0.3f, h * 0.05f), glm::vec2(w * 0.65f, h * 0.9f), 8, ResourceManager::getFont("default") ),
	prevState( MAIN )
{
	width = w;
	height = h;

	// initialize buttons
	bBack = Button( glm::vec2( w * 0.05f, h * 0.05f ), glm::vec2( w * 0.2f, h * 0.1f ) );
	bBack.setText( "Back" );
	bBack.setOnClickFunction( [&] () {
		current = prevState;
	} );

	// load background
	ResourceManager::loadTexture( "cave_water.jpg", GL_FALSE, "cave_water" );
	ResourceManager::loadTexture( "map.png", GL_TRUE, "map" );

	// load game rules from file
	tbRules.setPadding( 24, 24 );
	std::fstream rulesFile( ResourceManager::getPath( "text" ) + "rules.txt", std::ios_base::in );
	if ( rulesFile.is_open() ) {
		char tmp[1024];
		while ( rulesFile.good() ) {
			if ( rulesFile.peek() == '\n' ) {
				tbRules.addNewLine();
			}
			rulesFile.getline( tmp, 1024 );
			tbRules.addText( tmp, GL_TRUE );
		}

		rulesFile.close();
	} else {
		std::cout << "Failed to load rules file" << std::endl;
	}
}

Rules::~Rules()
{
}

void Rules::init() {
	current = RULES;
	tbRules.scrollToLine( 0 );
	ServiceLocator::getInput().addOnClickObserver( &bBack );
	ServiceLocator::getInput().addOnClickObserver( &tbRules );
	ServiceLocator::getInput().addOnScrollObserver( &tbRules );
}

STATE Rules::update() {
	if ( current != RULES ) {
		// unregister input listeners
		ServiceLocator::getInput().removeOnClickObserver( &bBack );
		ServiceLocator::getInput().removeOnClickObserver( &tbRules );
		ServiceLocator::getInput().removeOnScrollObserver( &tbRules );
	}
	return current;
}

void Rules::render() {
	ServiceLocator::getGraphics().draw2DTexture( ResourceManager::getTexture( "cave_water" ), glm::vec2( 0.0f ), glm::vec2( width, height ), 0.0f );
	tbRules.render( ServiceLocator::getGraphics() );
	bBack.render( ServiceLocator::getGraphics() );

	ServiceLocator::getGraphics().draw2DBox( glm::vec2( width * 0.05f, height * 0.45f ), glm::vec2( width * 0.2f, height * 0.5f ), glm::vec3( 0.0f ) );
	ServiceLocator::getGraphics().renderText( ResourceManager::getFont( "default" ), "Cave Map", glm::vec2( width * 0.15f, height * 0.5f ), 1.0f, glm::vec3( 1.0f ),
		HOR_CENTERED, VERT_CENTERED );
	ServiceLocator::getGraphics().draw2DTexture( ResourceManager::getTexture( "map" ), glm::vec2( width * 0.05f, height * 0.6f ), glm::vec2( width * 0.2f, height * 0.3f ), 0.0f );
}

void Rules::setPrevState( STATE s ) {
	prevState = s;
}

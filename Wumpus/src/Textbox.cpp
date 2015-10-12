#include "../includes/Textbox.h"
#include "../includes/Graphics.h"
#include "../includes/ResourceManager.h"

Textbox::Textbox( glm::vec2 pos, glm::vec2 size, GLfloat borderSize, const font& fontType, GLuint fontSize ) :
	pos(pos), size(size), borderSize(borderSize), fontType(fontType), fontSize(fontSize), borderColor(glm::vec3(0.0f)),
	backgroundColor(glm::vec3(1.0f)), textColor(glm::vec3(0.0f)), paddingHorizontal(8.0f), paddingVertical(8.0f), currHorizontalOffset(0.0f),
	currentLineNumber(0), lineSpacing(1.5f), firstLineInView(0)
{
}

Textbox::~Textbox()
{
}

void Textbox::addText( std::string newText )
{
	if ( newText.size() == 0 )
		return;

	// get edges
	GLuint leftEdge = pos.x + paddingHorizontal + borderSize;
	GLuint rightEdge = pos.x + size.x - paddingHorizontal - borderSize;

	// loop through each token of text
	std::string delimiter = " ";
	GLfloat delimOffset = fontType[32].advance >> 6;
	std::string token;
	GLuint start = 0;
	GLuint end = newText.find( delimiter );
	while ( end != std::string::npos ) {
		// get the next token
		token = newText.substr( start, end - start );

		// calculate the width of the token
		GLfloat width = getStringWidth( token );

		// check to see if token fits on the same line
		if ( leftEdge + currHorizontalOffset + width > rightEdge ){
			addNewLine();
		}
		tokens.push_back( StringToken( token, currHorizontalOffset, currentLineNumber ) );

		// move horizontal offset
		currHorizontalOffset += width + delimOffset;

		start = end + delimiter.length();
		end = newText.find( delimiter, start );
	}

	token = newText.substr( start, newText.size() );
	GLfloat width = getStringWidth( token );
	if ( currHorizontalOffset + paddingHorizontal + width > size.x ) {
		addNewLine();
	}
	tokens.push_back( StringToken( token, currHorizontalOffset, currentLineNumber ) );
	currHorizontalOffset += width + delimOffset;
}

void Textbox::addNewLine()
{
	currentLineNumber++;
	currHorizontalOffset = 0.0f;
	tokens.push_back( StringToken( "", currHorizontalOffset, currentLineNumber ) );
	// any time a new line is added, go to bottom of textbox
	firstLineInView = 0;
	if ( currentLineNumber >= getNumLinesThatFit() ) {
		firstLineInView = currentLineNumber + 1 - getNumLinesThatFit();
	}
}

void Textbox::setPadding( GLfloat horizontal, GLfloat vertical )
{
	paddingHorizontal = horizontal;
	paddingVertical = vertical;
}

void Textbox::setLineSpacing( GLfloat spacing ) {
	lineSpacing = spacing;
}

void Textbox::setTextColor( glm::vec3 color )
{
	textColor = color;
}

void Textbox::setBorderColor( glm::vec3 color )
{
	borderColor = color;
}

void Textbox::setBackgroundColor( glm::vec3 color )
{
	backgroundColor = color;
}

void Textbox::render( Graphics& graphics )
{
	// render border rectangle
	graphics.draw2DBox( pos, size, borderColor );
	// render background rectangle 
	graphics.draw2DBox( pos + borderSize, size - borderSize * 2.0f, backgroundColor );

	if ( tokens.size() == 0 )
		return;

	// get range of tokens to render based on which are in view
	int start = getFirstTokenOnLine( firstLineInView );
	int end = (firstLineInView + getNumLinesThatFit() - 1) < currentLineNumber ? getFirstTokenOnLine( firstLineInView + getNumLinesThatFit() ) : tokens.size();
	// render visible lines of text
	for ( int i = start; i < end; ++i ) {
		StringToken& token = tokens[i];
		GLfloat yPos = pos.y + paddingVertical + borderSize + fontType['H'].bearing.y * ( (token.lineNum - firstLineInView) * lineSpacing);
		graphics.renderText( fontType, sfw::string( token.str.c_str() ),
			glm::vec2( pos.x + paddingHorizontal + borderSize + token.xPos, yPos ), 1.0f, textColor );
	}
}

GLfloat	Textbox::getStringWidth( const std::string& str ) const {
	GLfloat width = 0;
	for ( char c : str ) {
		width += fontType.at( c ).advance >> 6;
	}
	return width;
}

GLuint Textbox::getNumLinesThatFit() const {
	GLuint num = ( ( size.y - ( paddingVertical + borderSize ) * 2.0f ) ) / ( lineSpacing * fontType.at( 'H' ).bearing.y );
	return num;
}

GLuint Textbox::getFirstTokenOnLine( GLuint line ) {
	if ( line < 0 || line > currentLineNumber || tokens.size() == 0 ) {
		return -1;
	}

	// implement inefficiently for now
	for ( int i = 0; i < tokens.size(); ++i ) {
		if ( tokens[i].lineNum == line ) {
			return i;
		}
	}
	return -1;
}

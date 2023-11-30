#pragma once

#include <vector>

#include <scanner/token.h>



// a Scanner takes a source and scans it into tokens
class Scanner
{
public:
	Scanner(const std::string& source);


	std::vector<Token> scan();


private:
	// resulting tokens
	std::vector<Token> tokens_;

	// source string
	std::string source_;

	// locality utils
	size_t line_, begin_, end_;
	size_t& current_ = end_;

	size_t ln_begin_, ln_end_;
	size_t& ln_current_ = ln_end_;


	TokenPosition position() const noexcept { return TokenPosition(line_, ln_begin_, ln_end_); }


	// scans the token
	void scan_token();

	void		string(const char encloser);		// processes a string token
	std::string advance_string(const char encloser);
	char		string_escape(const char escape);	// processes a string token escape characters

	void number() noexcept;					// processes a number token
	void advance_number() noexcept;			// advances to the end of a number token

	void identifier();						// processes a identifier (booleans, keywords, identifiers...) token


	bool at_end()		const	noexcept;
	char advance()				noexcept;
	char peek()			const	noexcept;
	char peek_next()	const	noexcept;

	bool match(const char next) noexcept;


	void add_token(const TokenType type, const Type& value = Type()) noexcept {
		tokens_.push_back(Token(type, current_substring(), value, line_, begin_, end_));
	}


	std::string current_substring() const noexcept {
		return source_.substr(begin_, end_ - begin_);
	}
};
#include <language/riv.h>

#include <scanner/token.h>



// all language operators
static std::map<std::string, TokenType> s_operators =
{
	{"+", TokenType::Plus            },
	{"-", TokenType::Minus           },
	{"*", TokenType::Star            },
	{"/", TokenType::Slash           },
	{">", TokenType::Greater         },
	{"<", TokenType::Lesser          },
	{"=", TokenType::Equal           },
	{"(", TokenType::LeftParen       },
	{")", TokenType::RightParen      },
	{"[", TokenType::LeftBrace       },
	{"]", TokenType::RightBrace      },
	{"{", TokenType::LeftCurlyBrace  },
	{"}", TokenType::RightCurlyBrace },
	{";", TokenType::SemiColon       },
	{".", TokenType::Dot             },
	{",", TokenType::Comma           },
	{"!", TokenType::Bang            }
};


// all language keywords
static std::map<std::string, TokenType> s_keywords =
{
	{"print"   , TokenType::Print    },
	{"var"     , TokenType::Var      },
	{"mut"     , TokenType::Mut      },
	{"imut"    , TokenType::Imut     },
	{"if"      , TokenType::If       },
	{"else"    , TokenType::Else     },
	{"while"   , TokenType::While    },
	{"for"     , TokenType::For      },
	{"loop"    , TokenType::Loop     },
	{"break"   , TokenType::Break    },
	{"continue", TokenType::Continue },
	{"function", TokenType::Function },
	{"return"  , TokenType::Return   },
	{"import"  , TokenType::Import   },
	{"package" , TokenType::Package  }
};


// non-statement keywords (modifiers)
static std::vector<TokenType> s_modifiers =
{
	TokenType::Mut, TokenType::Imut
};


// all language type keywords
static std::map<std::string, TokenType> s_type_keywords =
{
	{"true" , TokenType::Bool},
	{"false", TokenType::Bool},
	{"null" , TokenType::Null}
};



const std::map<std::string, TokenType>& lang_operators()     noexcept { return s_operators    ; }
const std::map<std::string, TokenType>& lang_keywords()      noexcept { return s_keywords     ; }
const std::vector<TokenType>          & lang_modifiers()     noexcept { return s_modifiers    ; }
const std::map<std::string, TokenType>& lang_type_keywords() noexcept { return s_type_keywords; }
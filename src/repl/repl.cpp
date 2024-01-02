#include <repl/repl.h>

#include <specter/output/color/painter/paint_rules.h>
#include <specter/output/color/painter/match_data.h>

#include <common/map.h>
#include <language/riv.h>



RivREPL::RivREPL()
{
	painter_.attach_cursor(m_cursor);

	// operators
	sp::MatcherRule* operators_rule = new sp::MatcherRule({}, 75);
	operators_rule->matchers = sp::Matcher::matchers_from_string_list(get_keys_from_map(lang_operators()));

	// keywords
	sp::MatcherRule* keywords_rule = new sp::MatcherRule({}, 170);
	keywords_rule->matchers = sp::Matcher::matchers_from_string_list(get_keys_from_map(lang_keywords()));

	// type keywords
	sp::MatcherRule* type_keywords_rule = new sp::MatcherRule({}, 215);
	type_keywords_rule->matchers = sp::Matcher::matchers_from_string_list(get_keys_from_map(lang_type_keywords()));


	painter_.add_rule(operators_rule);
	painter_.add_rule(keywords_rule);
	painter_.add_rule(type_keywords_rule);
	
	// numbers
	painter_.add_rule(new sp::CustomRule([] (sp::MatchData& data) {
		return sp::is_number(data.token.source);
	}, 227));

	// strings
	painter_.add_rule(new sp::BetweenRule({"\""}, {"\""}, 113));
	painter_.add_rule(new sp::BetweenRule({"\'"}, {"\'"}, 113));
}
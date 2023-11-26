#include <repl/repl.h>

#include <specter/output/color/painter/paint_rules.h>
#include <specter/output/color/painter/match_data.h>

#include <lang.h>



RivREPL::RivREPL()
{
	painter_.attach_cursor(m_cursor);

	// operators
	sp::MatcherRule* operators_rule = new sp::MatcherRule({}, sp::fg_bcyan);
	operators_rule->matchers = sp::Matcher::matchers_from_string_list(get_keys_from_map(lang_operators()));

	// keywords
	sp::MatcherRule* keywords_rule = new sp::MatcherRule({}, sp::fg_bmagenta);
	keywords_rule->matchers = sp::Matcher::matchers_from_string_list(get_keys_from_map(lang_keywords()));

	
	painter_.add_rule(operators_rule);
	painter_.add_rule(keywords_rule);
	
	// numbers
	painter_.add_rule(new sp::CustomRule([] (sp::MatchData& data) {
		return sp::is_number(data.token.source);
	}, sp::fg_byellow));

	// strings
	painter_.add_rule(new sp::BetweenRule({"\""}, {"\""}, sp::fg_bgreen));
	painter_.add_rule(new sp::BetweenRule({"\'"}, {"\'"}, sp::fg_bgreen));
}
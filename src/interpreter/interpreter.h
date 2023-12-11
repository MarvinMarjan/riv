#pragma once

#include <vector>

#include <statement/statement.h>
#include <expression/expression.h>
#include <environment/environment.h>



class Exception;


// interpret statements
class Interpreter : public ExpressionProcessor, public StatementProcessor
{
public:
	Interpreter() = default;

	void interpret(const std::vector<Statement*>& statements);


	Environment* global() noexcept { return environment.top(); }


	Environment environment;


private:
	friend class RivFunction;


	void process_expression	(ExpressionStatement&)	override;
	void process_block		(BlockStatement&)		override;
	void process_print		(PrintStatement&)		override;
	void process_var		(VarStatement&)			override;
	void process_if			(IfStatement&)			override;
	void process_while		(WhileStatement&)		override;
	void process_break		(BreakStatement&)		override;
	void process_continue	(ContinueStatement&)	override;
	void process_function	(FunctionStatement&)	override;
	void process_return		(ReturnStatement&)		override;
	void process_import		(ImportStatement&)		override;


	struct ScopeConfig
	{
		ScopeConfig() = default;
		ScopeConfig(const Environment& old_env, const Environment& new_env, const bool enclose_old)
			: old_env(old_env), new_env(new_env), enclose_old(enclose_old) {}

		Environment old_env;
		Environment new_env;
		
		bool enclose_old = true;
	};


	void execute_block(const std::vector<Statement*>& statements, const ScopeConfig& config);

	void execute(Statement* const statement) {
		statement->process(*this);
	}



	Type process_binary		(BinaryExpression&)		override;
	Type process_unary		(UnaryExpression&)		override;
	Type process_grouping	(GroupingExpression&)	override;
	Type process_literal	(LiteralExpression&)	override;
	Type process_identifier	(IdentifierExpression&)	override;
	Type process_assignment	(AssignmentExpression&)	override;
	Type process_call		(CallExpression&)		override;

	Type evaluate(Expression* const expr);



	static bool equals(const Type& left, const Type& right) noexcept;
	static bool truthy(const Type& value) noexcept;

	static bool are_values_of_type(const std::initializer_list<Type>& values, const TypeIndex type) noexcept;

	static void throw_if_type_differs(const std::initializer_list<Type>& values, const TypeIndex type, const Exception& err);
};
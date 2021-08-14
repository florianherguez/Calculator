#include "Parser.h"

/*
* Constructor
*/
Parser::Parser(Lexer* lexer) : m_lexer(lexer){}

/*
* extract number from the stream token
* handle unary minus
* handle parenthesis

    E   ->  NUMBER                                      ( double )
    E   ->  MINUS E                                     ( - expression )
    E   ->  LEFT_PARE B RIGHT_PARE                      ( ( addSub ) )

    E   ->  ID                                          ( saved double )
    E   ->  ID ASSIGNED B                               ( saved double = addSub ))
    
    E   ->  NARY LEFT_PARE B [COMA B ...] RIGHT_PARE    ( nary_fun( addSub [, addSub ...] )
*/
double Parser::parsePrimaryExpression()
{
    m_lexer->getNextToken();

    switch (m_lexer->getCurrentToken())
    {
    case ETokenType::NUMBER:
    {
        double d_number = m_lexer->getNumber();
        m_lexer->getNextToken();

        return d_number;
    }

    case ETokenType::MINUS:
        return -parsePrimaryExpression();

    case ETokenType::LEFT_PARE:
    {
        double d_result = parseAddSub();

        if (m_lexer->getCurrentToken() != ETokenType::RIGHT_PARE)
        {
            throw std::string("Synthax Error : missing bracket");
        }
        m_lexer->getNextToken();

        return d_result;
    }

    case ETokenType::ID:
    {
        //std::cout << "memoire" << std::endl;
        double& id = m_memory[m_lexer->getId()];
        m_lexer->getNextToken();

        if (m_lexer->getCurrentToken() == ETokenType::ASSIGN)
        {
            //std::cout << "assignement" << std::endl;
            id = parseAddSub();
        }
        //std::cout << "resultat id = " << id << std::endl;
        return id;
    }

    case ETokenType::NARY:
    {
        //std::cout << "unary function" << std::endl;
        std::string nary_fun = m_lexer->getId();

        m_lexer->getNextToken();

        if (m_lexer->getCurrentToken() != ETokenType::LEFT_PARE)
        {
            throw std::string("Synthax Error : unary function missing left bracket");
        }

        std::list<double> params;
        params.push_back(parseAddSub());

        while (m_lexer->getCurrentToken() == ETokenType::COMA)
        {
            params.push_back(parseAddSub());
        }

        if (m_lexer->getCurrentToken() != ETokenType::RIGHT_PARE)
        {
            throw std::string("Synthax Error : unary function missing right bracket");
        }

        m_lexer->getNextToken();
        try
        {
            return m_naries[nary_fun](params);
        }
        catch (std::string const& error)
        {
            std::cerr << error << std::endl;
        }
    }

    default:
        throw std::string("Synthax Error : expected primary expression");
    }
}

/*
* handle multiplication and division

    A   ->  E                       ( expression )
    A   ->  E MUL E                 ( expression * expression )
    A   ->  E DIV E                 ( expression / expression )
*/
double Parser::parseMulDiv()
{
    double d_result = parsePrimaryExpression();

    while (true)
    {
        switch (m_lexer->getCurrentToken())
        {
        case ETokenType::MUL:

            d_result *= parsePrimaryExpression();
            break;

        case ETokenType::DIV:
        {

            double d_temp = parsePrimaryExpression();
            if (d_temp != 0.0)
            {
                d_result /= d_temp;
                break;
            }
            else
            {
                throw std::string("Error : division by zero");
            }
        }

        default:
            return d_result;
        }
    }
}

/*
* handle addition and substraction

    B   ->  A                       ( multDiv )
    B   ->  A PLUS A                ( multDiv + multDiv )
    B   ->  A MINUS A               ( multDiv - multDiv )
*/
double Parser::parseAddSub()
{
    double d_result = parseMulDiv();

    while (true)
    {
        switch (m_lexer->getCurrentToken())
        {
        case ETokenType::PLUS:

            d_result += parseMulDiv();
            break;

        case ETokenType::MINUS:

            d_result -= parseMulDiv();
            break;

        default:
            return d_result;
        }
    }
}

/*
    S   ->  B
*/
double Parser::calculate()
{
    //std::cout << "debut du calcul" << std::endl;
    return parseAddSub();
}
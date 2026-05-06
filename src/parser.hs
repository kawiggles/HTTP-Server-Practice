module Main where

import Data.Char
import Control.Applicative

data TomlValue =
    TomlBool Bool
    | TomlString String
    | TomlInt Integer
    deriving (Show, Eq)

newtype Parser a = Parser
    { runParser :: String -> Maybe (String, a) 
    }

-- prove that Parser is a Functor using fmap
instance Functor Parser where
    fmap f (Parser p) = Parser $ \a -> do
        (a', b) <- p a
        Just (a', f b)

-- prove that Parser is Applicative using pure and <*>
instance Applicative Parser where
    pure f = Parser $ \a -> Just (a, f)
    Parser t <*> Parser u = Parser $ \input -> do
        (input', f) <- t input
        (input'', a) <- u input'
        Just (input'', f a)

-- prove that Parser is Alternative using <|>
instance Alternative Parser where
    empty = Parser $ const Nothing
    (Parser f) <|> (Parser g) = Parser $ \input -> f input <|> g input

-- universal parser, constructed from three typed parsers
tomlValue :: Parser TomlValue
tomlValue = tomlBool <|> tomlInt <|> tomlString

tomlBool :: Parser TomlValue
tomlBool = f <$> (stringP "true" <|> stringP "false")
    where f "true" = TomlBool True
          f "false" = TomlBool False
          f _ = undefined

stringLiteral :: Parser String
stringLiteral = spanP (/='"')

tomlString :: Parser TomlValue
tomlString = TomlString <$> (charP '"' *> stringLiteral <* charP '"')

spanP :: (Char -> Bool) -> Parser String
spanP f = Parser $ \input ->
    let (token, extra) = span f input
    in Just (extra, token)

notNull :: Parser [a] -> Parser [a]
notNull (Parser p) = Parser $ \input -> do
    (input', xs) <- p input
    if null xs
        then Nothing
        else Just (input', xs)

tomlInt :: Parser TomlValue
tomlInt = f <$> notNull (spanP isDigit)
    where f ds = TomlInt $ read ds

stringP :: String -> Parser String
stringP = traverse charP

charP :: Char -> Parser Char
charP x = Parser f
    where
        f (y:ys)
            | y == x = Just (ys, x)
            | otherwise = Nothing
        f [] = Nothing

main :: IO ()
main = undefined

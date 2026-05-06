{-# LANGUAGE ForeignFunctionInterface #-}

import Foreign.C.String
import Foreign.C.Types
import Foreign.Storable
import Foreign.Ptr
import Foreign.Marshal.Array

instance Storable ServerConfig where
    sizeOf _ = sizeOf (undefined :: CInt) + 4096
    alignment _ = alignment (undefined :: CInt)

    peek ptr = do
        portVal <- peekByteOff ptr 0
        rootVal <- peekByteOff ptr (sizeOf (undefined :: CInt))
        return $ ServerConfig portVal rootVal

    poke ptr config = do
        pokeByteOff ptr 0 (port config)
        withCString (root config) $ \cstr ->
            copyArray (plusPtr ptr 4) cstr (length (root config) + 1)

data ServerConfig = ServerConfig
    { port :: CInt
    , root :: String
    }

foreign export ccall parseConfig :: CString -> Ptr ServerConfig -> IO ()
parseConfig :: CString -> Ptr ServerConfig -> IO ()
parseConfig pathCStr ptr = do
    path <- peekCString pathCStr
    toml <- readFile path
    parseToml toml

{-
parseToml :: String -> ServerConfig
parseToml toml =
    let ls = lines toml
-}

data TomlValue = 
    TomlBool Bool
    | TomlString String
    | TomlInt Integer

# fprime
f' virtual machine described in my compiler series

## Dependencies
flex `2.5.37`
bision `(GNU Bison) 3.0.4`
clang `version 4.0.0`

## Brew Configs

Bison
```
  url "https://ftpmirror.gnu.org/bison/bison-3.0.4.tar.gz"
      mirror "https://ftp.gnu.org/gnu/bison/bison-3.0.4.tar.gz"
      sha256 "b67fd2daae7a64b5ba862c66c07c1addb9e6b1b05c5f2049392cfd8a2172952e"
```

Flex
```
             url "http://downloads.sourceforge.net/flex/flex-2.5.37.tar.bz2"
               sha256 "17aa7b4ebf19a13bc2dff4115b416365c95f090061539a932a68092349ac052a"    
```

clang (latest versions should work)
```
brew install --with-clang llvm
```

##

Tested with MacOSX
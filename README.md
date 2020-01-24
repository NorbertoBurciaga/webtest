# webtest

Web server test in C++ using restinio

## Contents

* [Project Hierarchy](#project-hierarchy)
* [Getting Started](#getting-started)
* [Testing](#testing)
* [Support](#support)
* [FAQ](#faq)
* [Development](#development)
* [License](#license)
* [References](#references)

## Project Hierarchy

```console
```

[Contents](#contents)


## Getting Started

### Requirements


### Installation

#### How to install dependency packages

```console
sudo su
apt update && \
     apt upgrade -y && \
     DEBIAN_FRONTEND=noninteractive apt install -y curl libicu-dev git-all \
     gcc g++ flex bison make autoconf automake libtool autotools-dev \
     libevent-dev zlib1g-dev pkg-config libssl-dev libsnappy-dev libbz2-dev \
     liblz4-dev libzstd-dev net-tools tree graphviz texlive-latex-base \
     dumpasn1 ruby-full ruby-dev ruby-rspec rake rubygems bundler
```
#### How to install cmake

```console
sudo su
curl -LO https://cmake.org/files/LatestRelease/cmake-3.15.0.tar.gz && \
    tar -xzf cmake-3.15.0.tar.gz && \
    cd cmake-3.15.0 && \
    ./bootstrap --prefix=/usr/local && \
    make -j$(nproc) && \
    sudo make install && \
    cd .. && \
    rm -rf cmake-3.15.0.tar.gz ./cmake-3.15.0
```

#### How to install Boost

```console
sudo su
curl -LO https://dl.bintray.com/boostorg/release/1.71.0/source/boost_1_71_0.tar.bz2 && \
    tar -xjf boost_1_71_0.tar.bz2 && \
    cd boost_1_71_0 && \
    ./bootstrap.sh --prefix=/usr/local && \
    user_configFile=`find $PWD -name user-config.jam` && \
    echo "using mpi;" >> $user_configFile && \
    ./b2 -q -j$(nproc) install && \
    cd .. && \
    rm -rf boost_1_71_0.tar.bz2 ./boost_1_71_0
```

#### How to install restinio

Restinio is a header-only C++14 library that gives you an embedded HTTP server with nice express-like routing (although it is not mandatory to use router) and websockets on board. It is targeted primarily for asynchronous processing of HTTP-requests.

```console
$ git clone https://github.com/Stiffstream/restinio.git
$ sudo gem install Mxx_ru
$ cd restinio
$ mxxruexternals
$ cd dev
$ mkdir build
$ cd build
$ cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release ..
$ sudo cmake --build . --config Release --target install
```

#### How to create a self-signed Certificate for TLS

It is required to generate some files to activate the TLS and use https. The private key, the certificate and the Diffie-Hellman parameters

```console
$ openssl req -newkey rsa:2048 -nodes -keyout privateKey.pem -x509 -days 365 -out certificate.pem
$ openssl dhparam -out dhparams.pem 2048
```

To check the certificate:

```console
$ openssl x509 -text -noout -in certificate.pem
```

[Contents](#contents)


## Testing


```console
$ 
```

[Contents](#contents)



## Support

Technical support is available in 

[Contents](#contents)

## FAQ

[Contents](#contents)


## Development

If you want to contribute:


### Process

1. Review the Contribution License Agreement
   1.1. Defines the terms under which intellectual property is contributed to a project
   1.2. To ensure the owner of the project has the necessary ownership, or grants of rights over contributions made by third parties.
   1.3. Must be signed by any contributor to a project who is making a "significant contribution".
   1.4. Without that signed CLA the contribution will not be accepted.
2. Check the project issues list
3. Fork the repository
4. Submit your contribution as a pull request

### Discuss your Change
- Create/update an issue
- A committer approves the proposal

### Making changes

Making a copy of the project's code
Make your code changes
Keep your changes concise and easy for the maintainers to understand
Refer back to any discussion you had on the projects issues list
Stick to the scope of the issue
Make sure to fully test your code
Make sure to include any required documentation
Remember your contributions represent your public reputation and that of DXC

### Submitting Changes
- Request review
- Create a contribution request (Pull Request) which include:
  - Your code changes
  - A commit message describing what you're submitting
  - A reference to the original issue you created/updated in step 1  


[Contents](#contents)


## License

See LICENSE file

[Contents](#contents)


## References

<a name="ref1"></a>
1. https://cmake.org/
<a name="ref2"></a>
2. http://www.boost.org

[Contents](#contents)
<h1 align="center">💬 ft_irc</h1>

<p align="center">
	<b><i>ft_irc is a project from the 42 school, focused on creating an IRC server following standard internet communication protocols. The server's performance is evaluated using a real IRC client.</i></b><br>
</p>

<p align="center">
	<img alt="Top used language" src="https://img.shields.io/github/languages/top/okbrandon/ft_irc?color=success"/>
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/okbrandon/ft_irc"/>
</p>

## 📚 Table of Contents

- [📚 Table of Contents](#-table-of-contents)
- [👨‍🏫 Quick demonstration](#-quick-demonstration)
- [📦 Installation](#-installation)
- [📝 Usage](#-usage)
- [📝 Example](#-example)
- [📎 References](#-references)

## 👨‍🏫 Quick demonstration

https://github.com/okbrandon/ft_irc/assets/103316367/8359cad2-4526-43f4-b7f7-24c0212094e8
> Basic demonstration

https://github.com/okbrandon/ft_irc/assets/103316367/2568c418-c344-4e15-8cea-1d96a4ac0db2
> Demonstration with our chatbot powered with OpenAI.

## 📦 Installation

Clone the repository from GitHub:
```sh
git clone https://github.com/okbrandon/ft_irc.git
```

Compile the `server` executable:
```sh
make
```

Compile the `server` executable with debug logs:
```sh
make logs
```
> With this executable you'll be able to see every input going to the server and every output from the server.

> [!NOTE]
> The executable contains the `mandatory` and `bonus` part combined. <br />
> Our reference client is [`IRSSI`](https://irssi.org/).

## 📝 Usage

Run the `server` executable:
```sh
./ircserv <port> <password>
```
> Where the `port` parameter is on which your IRC server will be listening to for incoming IRC connections.
> And `password` is the connection password. It will be needed by any IRC client that tries to connect to your server.

> [!NOTE]
> Be aware that the `port` should only be between `1` inclusive and `65535` exclusive.

## 📝 Example

The subject asks to implement the following commands: `KICK`, `TOPIC`, `INVITE` and `MODE` with the flags `i`, `t`, `k`, `o` and `l`.
We also implemented other commands such as: `PRIVMSG`, `CAP`, `JOIN`, `NICK`, `PART`, `PING`, `QUIT` and `USER`.

When joining the server with our reference client, you should be automatically authentified.
![welcome-img](https://github.com/okbrandon/ft_irc/assets/103316367/fdd441d1-7ea3-4e72-81d3-c24b9319cd83)
From here you can send other commands, for instance if you want to create a channel or join an existing one use: `/JOIN myChannel`. Now you're inside a channel, you can send messages and do what ever you want on this wonderful server! :)
![inside-channel-img](https://github.com/okbrandon/ft_irc/assets/103316367/3052c1d7-8ae3-41f2-8ecc-32843c249cdd)

## 📎 References

- [IRC numeric list](https://www.alien.net.au/irc/irc2numerics.html)
- [IRC numeric replies : RFC 1459](http://www.iprelax.fr/irc/irc_rfcus6.php)
- [Learn I/O polling](https://github.com/pniewiejski/learn-io-polling)

[⬆ Back to Top](#-table-of-contents)

## 🌏 Meta

bsoubaig - bsoubaig@student.42nice.fr <br />
evmorvan - evmorvan@student.42nice.fr

#ifndef MCL_TERMINAL_MANIPULATION_H
#define MCL_TERMINAL_MANIPULATION_H

#include <termios.h>
#include <unistd.h>
#include <string>
#include "strmanip.h"


namespace mcl
{
	namespace aec //ANSI escape codes
	{
		#define AEC_CSI "\x1B["
		struct pos
		{
			unsigned short int x, y;
			pos(std::string s) : x{0}, y{0}
			{
				auto l = split(s, ';');
				if (l.size() != 2)
					throw std::domain_error("[mcl::aec::pos::pos] Bad string");
				y = getB10(l[0]) - 1;
				x = getB10(l[1]) - 1;
			}
			pos(unsigned short int x, unsigned short int y) : x{x}, y{y} { }
		};
		#define AEC_UP(x) AEC_CSI #x "A"
		std::string up(unsigned short int i)
		{
			if (!i)
				return "";
			std::string out{AEC_CSI};
			return pushB10(out, i) + 'A';
		}
		#define AEC_DOWN(x) AEC_CSI #x "B"
		std::string down(unsigned short int i)
		{
			if (!i)
				return "";
			std::string out{AEC_CSI};
			return pushB10(out, i) + 'B';
		}
		#define AEC_FORWARD(x) AEC_CSI #x "C"
		std::string forward(unsigned short int i)
		{
			if (!i)
				return "";
			std::string out{AEC_CSI};
			return pushB10(out, i) + 'C';
		}
		#define AEC_BACKWARD(x) AEC_CSI #x "D"
		std::string backward(unsigned short int i)
		{
			if (!i)
				return "";
			std::string out{AEC_CSI};
			return pushB10(out, i) + 'D';
		}
		std::string absolute(const pos& p)
		{
			std::string out{AEC_CSI};
			pushB10(out, p.y+1) += ';';
			pushB10(out, p.x+1) += 'H';
			return out;
		}
		std::string absolute(unsigned short int x, unsigned short int y)
		{
			std::string out{AEC_CSI};
			pushB10(out, y+1) += ';';
			pushB10(out, x+1) += 'H';
			return out;
		}
		#define AEC_ERASE_SE AEC_CSI "0J"
		#define AEC_ERASE_SB AEC_CSI "1J"
		#define AEC_ERASE_SA AEC_CSI "2J"
		#define AEC_ERASE_AA AEC_CSI "3J"
		#define AEC_ERASE_LE AEC_CSI "0K"
		#define AEC_ERASE_LB AEC_CSI "1K"
		#define AEC_ERASE_LA AEC_CSI "2K"
		std::string scrollUp(unsigned short int i)
		{
			std::string out{AEC_CSI};
			return pushB10(out, i) + 'S';
		}
		std::string scrollDown(unsigned short int i)
		{
			std::string out{AEC_CSI};
			return pushB10(out, i) + 'T';
		}
		#define AEC_DSI AEC_CSI "6n"

		#define AEC_SGR(x) AEC_CSI #x "m"

		#define AEC_RESET AEC_SGR(0)
		#define AEC_BOLD AEC_SGR(1)
		#define AEC_FAINT AEC_SGR(2)
		#define AEC_ITALIC AEC_SGR(3)
		#define AEC_UNDERLINE AEC_SGR(4)
		#define AEC_SLOW_BLINK AEC_SGR(5)
		#define AEC_RAPID_BLINK AEC_SGR(6)
		#define AEC_INVERT AEC_SGR(7)
		#define AEC_HIDE AEC_SGR(8)
		#define AEC_STRIKE_THROUGH AEC_SGR(9)
		#define AEC_PRIMARY_FONT AEC_SGR(10)
		#define AEC_BLACKLETTER AEC_SGR(20)
		#define AEC_DOUBLE_UNDERLINE AEC_SGR(21)
		#define AEC_NORMAL_INTENSITY AEC_SGR(22)
		#define AEC_NOT_ITALIC_OR_BLACKLETTER AEC_SGR(23)
		#define AEC_NOT_UNDERLINED AEC_SGR(24)
		#define AEC_NOT_BLINKING AEC_SGR(25)
		#define AEC_NOT_REVERSED AEC_SGR(27)
		#define AEC_NOT_HIDDEN AEC_SGR(28)
		#define AEC_NOT_STRUCK_THROUGH AEC_SGR(29)

		#define AEC_BLACK_FG AEC_SGR(30)
		#define AEC_RED_FG AEC_SGR(31)
		#define AEC_GREEN_FG AEC_SGR(32)
		#define AEC_YELLOW_FG AEC_SGR(33)
		#define AEC_BLUE_FG AEC_SGR(34)
		#define AEC_MAGENTA_FG AEC_SGR(35)
		#define AEC_CYAN_FG AEC_SGR(36)
		#define AEC_WHITE_FG AEC_SGR(37)
		#define AEC_DEFAULT_FG AEC_SGR(39)

		#define AEC_BLACK_BG AEC_SGR(40)
		#define AEC_RED_BG AEC_SGR(41)
		#define AEC_GREEN_BG AEC_SGR(42)
		#define AEC_YELLOW_BG AEC_SGR(43)
		#define AEC_BLUE_BG AEC_SGR(44)
		#define AEC_MAGENTA_BG AEC_SGR(45)
		#define AEC_CYAN_BG AEC_SGR(46)
		#define AEC_WHITE_BG AEC_SGR(47)
		#define AEC_DEFAULT_BG AEC_SGR(49)

		#define AEC_FRAMED AEC_SGR(51)
		#define AEC_ENCIRCLED AEC_SGR(52)
		#define AEC_OVERLINED AEC_SGR(53)
		#define AEC_NOT_FRAMED_ENCIRCLED AEC_SGR(54)
		#define AEC_NOT_OVERLINED AEC_SGR(55)

		#define AEC_BRIGHT_BLACK_FG AEC_SGR(90)
		#define AEC_BRIGHT_RED_FG AEC_SGR(91)
		#define AEC_BRIGHT_GREEN_FG AEC_SGR(92)
		#define AEC_BRIGHT_YELLOW_FG AEC_SGR(93)
		#define AEC_BRIGHT_BLUE_FG AEC_SGR(94)
		#define AEC_BRIGHT_MAGENTA_FG AEC_SGR(95)
		#define AEC_BRIGHT_CYAN_FG AEC_SGR(96)
		#define AEC_BRIGHT_WHITE_FG AEC_SGR(97)

		#define AEC_BRIGHT_BLACK_BG AEC_SGR(100)
		#define AEC_BRIGHT_RED_BG AEC_SGR(101)
		#define AEC_BRIGHT_GREEN_BG AEC_SGR(102)
		#define AEC_BRIGHT_YELLOW_BG AEC_SGR(103)
		#define AEC_BRIGHT_BLUE_BG AEC_SGR(104)
		#define AEC_BRIGHT_MAGENTA_BG AEC_SGR(105)
		#define AEC_BRIGHT_CYAN_BG AEC_SGR(106)
		#define AEC_BRIGHT_WHITE_BG AEC_SGR(107)

		#define AEC_HIDE_CURSOR AEC_CSI "?25l"
		#define AEC_SHOW_CURSOR AEC_CSI "?25h"
	}

	class tty
	{
	public:


		tty() : fd{0}
		{
			tcgetattr(fd, &t);
		}


		//Returns previous state
		termios update()
		{
			auto old = t;
			tcgetattr(fd, &t);
			return old;
		}

		//Returns previous state
		termios uncook()
		{
			auto old = update();

			t.c_lflag &= ~(ECHO | ICANON); //Unset auto-echo and canonical mode
			tcsetattr(fd, TCSAFLUSH, &t); //Save new state

			return old;
		}

		//Returns previous state
		termios cook()
		{
			auto old = update();

			t.c_lflag |= ECHO | ICANON; //Set auto-echo and canonical mode
			tcsetattr(fd, TCSAFLUSH, &t); //Save new state

			return old;
		}

		termios setState(termios a)
		{
			auto old = t;
			t = a;
			tcsetattr(fd, TCSAFLUSH, &t);
			return old;
		}

		/* NOTE:  This assumes that `fd` (most likely stdin) is currently empty.
				It will not work otherwise, nor will it throw to indicate.
				Make certain you have eaten all input before using this.
				*/
		aec::pos getPos()
		{
			auto old = uncook();
			write(fd, "\x1B[6n", 4);
			char c[2];
			read(fd, c, 2);
			aec::pos p{0,0};
			while (read(fd, c, 1), *c != ';')
				(p.y *= 10) += *c - '0';
			while (read(fd, c, 1), *c != 'R')
				(p.x *= 10) += *c - '0';
			setState(old);
			--p.x;
			--p.y;
			return p;
		}
		/* NOTE:  This assumes that `fd` (most likely stdin) is currently empty.
				It will not work otherwise, nor will it throw to indicate.
				Make certain you have eaten all input before using this.
				*/
		tty& aquireSize()
		{
			auto olds = uncook();
			char old[16];
			int len = 0;
			write(fd, "\x1B[6n", 4);
			while (read(fd, old+len, 1), old[len] != 'R')
				++len;
			old[len++] = 'H';


			write(fd, "\x1B[999;999H", 10);
			auto corner = getPos();
			w = corner.x + 1;
			h = corner.y + 1;

			write(fd, old, len);
			setState(olds);
			return *this;
		}
		int getWidth() const { return w; }
		int getHeight() const { return h; }

	private:
		int fd;
		termios t;

		int w = -1, h = -1;
	};
}


#endif
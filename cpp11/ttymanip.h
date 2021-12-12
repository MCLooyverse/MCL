#if __cplusplus < 201103L
	#error "Included version of mcl/ttymanip.h meant for at least C++11.  Do not directly include mcl/cpp11/ttymanip.h; use mcl/ttymanip.h instead."
#endif

#ifndef MCL_TERMINAL_MANIPULATION_H
#define MCL_TERMINAL_MANIPULATION_H

#include <termios.h>
#include <unistd.h>
#include <string>
#include <signal.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "typedefs.h"
#include "strmanip.h"


namespace mcl
{
	namespace tty
	{
		void init(
			bool captureCtrls
		);
		void uninit();


		struct pos;

		pos getCurs();
	}
	namespace aec //ANSI escape code
	{
		/**
		 * Control Sequence Introducer
		 * is the prefix for basically
		 * all useful escape codes.
		 */
		#define AEC_CSI "\x1B["

		/**
		 * Macros for literal movements
		 * and functions for dynamic
		 * movement of the terminal
		 * cursor
		 */
		#define AEC_CUU(x) AEC_CSI #x "A"
		std::string cuu(usint);
		#define AEC_CUD(x) AEC_CSI #x "B"
		std::string cud(usint);
		#define AEC_CUF(x) AEC_CSI #x "C"
		std::string cuf(usint);
		#define AEC_CUB(x) AEC_CSI #x "D"
		std::string cub(usint);

		/**
		 * Move cursor to an absolute
		 * position, either with `pos`
		 * type, or with line and
		 * column numbers.
		 */
		std::string abs(mcl::tty::pos);
		std::string abs(usint,usint);
		#define AEC_ABS(l,c) AEC_CSI #l ";" #c "H"

		/**
		 * Erase parts of the screen
		 * - From cursor to end-of-screen
		 * - From cursor to start-of-screen
		 * - Whole screen
		 * - Whole screen, and scrollback buf
		 * - From cursor to end-of-line
		 * - From cursor to start-of-line
		 */
		#define AEC_ERASE_SE AEC_CSI "0J"
		#define AEC_ERASE_SB AEC_CSI "1J"
		#define AEC_ERASE_SA AEC_CSI "2J"
		#define AEC_ERASE_AA AEC_CSI "3J"
		#define AEC_ERASE_LE AEC_CSI "0K"
		#define AEC_ERASE_LB AEC_CSI "1K"
		#define AEC_ERASE_LA AEC_CSI "2K"

		/**
		 * Scroll screen up and down
		 */
		#define AEC_SSU(x) AEC_CSI #x "S"
		std::string ssu(usint);
		#define AEC_SSD(x) AEC_CSI #x "T"
		std::string ssd(usint);

		/**
		 * Ask terminal to report the
		 * position of the cursor.
		 */
		#define AEC_DSR AEC_CSI "6n"

		/**
		 * Select Graphic Rendition
		 * allows for messing with a
		 * ton of graphical things.
		 */
		#define AEC_SGR(x) AEC_CSI #x "m"


		#define AEC_RESET                    AEC_SGR(0)
		#define AEC_BOLD                     AEC_SGR(1)
		#define AEC_FAINT                    AEC_SGR(2)
		#define AEC_ITALICS                  AEC_SGR(3)
		#define AEC_UNDERLINE                AEC_SGR(4)
		#define AEC_SLOW_BLINK               AEC_SGR(5)
		#define AEC_RAPID_BLINK              AEC_SGR(6)
		#define AEC_INVERT                   AEC_SGR(7)
		#define AEC_HIDE                     AEC_SGR(8)
		#define AEC_STRIKE                   AEC_SGR(9)
		#define AEC_PRIMARY_FONT             AEC_SGR(10)
		#define AEC_BLACKLETTER              AEC_SGR(20)
		#define AEC_DOUBLE_UNDERLINE         AEC_SGR(21)
		#define AEC_NO_BOLD_FAINT            AEC_SGR(22)
		#define AEC_NO_ITALICS_BLACKLETTER   AEC_SGR(23)
		#define AEC_NO_UNDERLINE             AEC_SGR(24)
		#define AEC_NO_BLINK                 AEC_SGR(25)
		#define AEC_NO_INVERT                AEC_SGR(27)
		#define AEC_NO_HIDE                  AEC_SGR(28)
		#define AEC_NO_STRIKE                AEC_SGR(29)

		/**
		 * Foreground (text) colors
		 */
		#define AEC_BLACK_FG                 AEC_SGR(30)
		#define AEC_RED_FG                   AEC_SGR(31)
		#define AEC_GREEN_FG                 AEC_SGR(32)
		#define AEC_YELLOW_FG                AEC_SGR(33)
		#define AEC_BLUE_FG                  AEC_SGR(34)
		#define AEC_MAGENTA_FG               AEC_SGR(35)
		#define AEC_CYAN_FG                  AEC_SGR(36)
		#define AEC_WHITE_FG                 AEC_SGR(37)
		#define AEC_DEFAULT_FG               AEC_SGR(39)

		/**
		 * Background colors
		 */
		#define AEC_BLACK_BG                 AEC_SGR(40)
		#define AEC_RED_BG                   AEC_SGR(41)
		#define AEC_GREEN_BG                 AEC_SGR(42)
		#define AEC_YELLOW_BG                AEC_SGR(43)
		#define AEC_BLUE_BG                  AEC_SGR(44)
		#define AEC_MAGENTA_BG               AEC_SGR(45)
		#define AEC_CYAN_BG                  AEC_SGR(46)
		#define AEC_WHITE_BG                 AEC_SGR(47)
		#define AEC_DEFAULT_BG               AEC_SGR(49)

		/**
		 * More random things
		 */
		#define AEC_FRAME                    AEC_SGR(51)
		#define AEC_ENCIRCLE                 AEC_SGR(52)
		#define AEC_OVERLINE                 AEC_SGR(53)
		#define AEC_NO_FRAME_ENCIRCLE        AEC_SGR(54)
		#define AEC_NO_OVERLINE              AEC_SGR(55)

		/**
		 * More text colors
		 */
		#define AEC_BRIGHT_BLACK_FG          AEC_SGR(90)
		#define AEC_BRIGHT_RED_FG            AEC_SGR(91)
		#define AEC_BRIGHT_GREEN_FG          AEC_SGR(92)
		#define AEC_BRIGHT_YELLOW_FG         AEC_SGR(93)
		#define AEC_BRIGHT_BLUE_FG           AEC_SGR(94)
		#define AEC_BRIGHT_MAGENTA_FG        AEC_SGR(95)
		#define AEC_BRIGHT_CYAN_FG           AEC_SGR(96)
		#define AEC_BRIGHT_WHITE_FG          AEC_SGR(97)

		/**
		 * More background colors
		 */
		#define AEC_BRIGHT_BLACK_BG          AEC_SGR(100)
		#define AEC_BRIGHT_RED_BG            AEC_SGR(101)
		#define AEC_BRIGHT_GREEN_BG          AEC_SGR(102)
		#define AEC_BRIGHT_YELLOW_BG         AEC_SGR(103)
		#define AEC_BRIGHT_BLUE_BG           AEC_SGR(104)
		#define AEC_BRIGHT_MAGENTA_BG        AEC_SGR(105)
		#define AEC_BRIGHT_CYAN_BG           AEC_SGR(106)
		#define AEC_BRIGHT_WHITE_BG          AEC_SGR(107)

		/**
		 * The rest is not always supported
		 */
		/**
		 * Save and restore cursor position
		 */
		#define AEC_SAVE_CURS                 AEC_CSI "s"
		#define AEC_REST_CURS                 AEC_CSI "u"

		/**
		 * Apparently not always supported.
		 * Hides and unhides the cursor.
		 */
		#define AEC_HIDE_CURS              AEC_CSI "?25l"
		#define AEC_SHOW_CURS              AEC_CSI "?25h"
	}

	namespace tty
	{
		/*This namespace is just a class
		 *which is supposed to always have exactly
		 *one instance.
		 */



		struct pos
		{
			int line, column;
		};


		termios oldterm;



		/*Pipe for any message presumably from not the user, but the
		 *Terminal itself
		 * /
		int ttymsg[2];
		int& tmin = ttymsg[0];
		int& tmout = ttymsg[1];
		*/
		key_t ttymsgkey;
		int ttymsg;
		const size_t MAXTMS = 8;
		struct tmb //Terminal Message Buffer
		{
			long int mtype;
			int msg[MAXTMS];
		};

		volatile sig_atomic_t winh = 0, winw = 0;

		int splitterPID = 0;
		int oldstdin = -1;


		/**
			* Sets up various things:
			* - Uncooks the terminal so that everything
			* 	comes straight to the program
			* - Handle terminal window resizing
			* - Fork a process to split stdin into our
			* 	(new) stdin, and into a different pipe
			* 	holding AECs from (old) stdin
			*/
		void init(
			bool captureCtrls = 0 //If true, unbinds all ^[anything] from the terminal
			)
		{
			//Only allow this function to be called once
			static bool called = 0;
			if (called)
				return;
			called = 1;

			atexit(uninit);

			//Uncook terminal
			tcgetattr(0, &oldterm);
			termios term = oldterm;

			//cfmakeraw(&term);
			term.c_lflag &= ~(ECHO | ICANON);

			tcsetattr(0, TCSAFLUSH, &term);

			//Split stdin into new stdin and tty message queue
			ttymsgkey = ftok(__FILE__, getpid());
			ttymsg = msgget(ttymsgkey, 0666 | IPC_CREAT);
			int newstdin[2];
			pipe(newstdin);
			splitterPID = fork();
			if (!splitterPID) //chid is 0, so this is the child
			{
				close(1); //Unlink stdout from tty
				dup(newstdin[1]); //Link stdout to write to parent's stdin
				close(newstdin[0]); //Don't need to read what we write
				for (std::string s;;)
				{
					char c;
					read(0, &c, 1);
					if (c == '\x1B')
					{
						s = "\x1B";
						for (; !isAlpha(c); read(0, &c, 1), s += c);
						if (c == 'R')
						{
							auto resp = split(s, ';');
							assert(resp.size() == 2);
							tmb msg{'R',
								{ getB10(resp[0]), getB10(resp[1]),
									0,0,0,0,0,0 }
							};
							msgsnd(ttymsg, &msg, sizeof(int)*MAXTMS, 0);
						}
						else
							write(1, s.c_str(), s.size());
					}
					else
						write(1, &c, 1);
				}
			}
			oldstdin = dup(0); //Copy raw stdin somewhere else
			close(0); //Don't want raw stdin
			dup(newstdin[0]); //Only user input
			close(newstdin[1]); //Don't need to write to our input

			//Register handler for SIGnal WINdow CHange
			struct sigaction sa;
			sa.sa_handler = (void (*)(int))[](int)->void{
				auto old = mcl::aec::abs(mcl::tty::getCurs());
				write(1, AEC_ABS(999,999), sizeof(AEC_ABS(999,999))-1);
				auto newc = mcl::tty::getCurs();
				winh = newc.line + 1;
				winw = newc.column + 1;
				write(1, old.c_str(), old.size());
			};
			sa.sa_flags = 0;
			sigemptyset(&sa.sa_mask);

			sigaction(SIGWINCH, &sa, 0);
			raise(SIGWINCH);
		}


		void uninit()
		{
			kill(splitterPID, SIGKILL);
			splitterPID = 0;
			close(0);
			dup(oldstdin);
			close(oldstdin);

			msgctl(ttymsg, IPC_RMID, 0);

			tcsetattr(0, TCSAFLUSH, &oldterm);
		}









		pos getCurs()
		{
			write(1, AEC_DSR, sizeof(AEC_DSR)-1);
			tmb in;
			msgrcv(ttymsg, &in, sizeof(int)*MAXTMS, 'R', 0);
			return pos{in.msg[0]-1, in.msg[1]-1};
		}



	}

	namespace aec
	{
		std::string cuu(usint n)
		{
			std::string out = AEC_CSI;
			return pushB10(out, n) += "A";
		}
		std::string cud(usint n)
		{
			std::string out = AEC_CSI;
			return pushB10(out, n) += "B";
		}
		std::string cuf(usint n)
		{
			std::string out = AEC_CSI;
			return pushB10(out, n) += "C";
		}
		std::string cub(usint n)
		{
			std::string out = AEC_CSI;
			return pushB10(out, n) += "D";
		}

		std::string abs(mcl::tty::pos p)
		{
			std::string out = AEC_CSI;
			return pushB10(pushB10(out, p.line+1) += ";", p.column+1) += "H";
		}
		std::string abs(usint l, usint c)
		{
			std::string out = AEC_CSI;
			return pushB10(pushB10(out, l+1) += ";", c+1) += "H";
		}

		std::string ssu(usint n)
		{
			std::string out = AEC_CSI;
			return pushB10(out, n) += "S";
		}
		std::string ssd(usint n)
		{
			std::string out = AEC_CSI;
			return pushB10(out, n) += "T";
		}
	}
}


#endif


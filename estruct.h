/* estruct.h
 * This file defines core structs for the editor.
 * The struct window contains variables such as
 * filename, number of columsn/rows in terminal,
 * number of rows in file, and also cursor position.
 * It also contains an array of row structs, which each
 * contain a string, representing the text in that row,
 * and also the size. This array of row structs is displayed
 * onto the buffer in buffer.c, thus rendering the contents
 * of the file.
 */

#define INSERT_MODE 1
#define COMMAND_MODE 0

struct window {
	int cx, cy;
	int absolute_cy; /* y-coordinate in relation to the terminal dimensions */
	char *fname; /* file name */
	int nsaved; /* if this is equal to 1, then file has been changed
                     * but not saved. Eventually, this will cause an
                     * asterix to appear on the status bar next to the
                     * file name
                     */
	int ncol, nrow;
	struct row *rows;
	int numrows; /* the number of rows in the file */
	int rfile; /* This flag indicates whether we should be
		      reading from the file or not, so we only do it
		      once. If we read from the file each time we refreshed
		      the screen, we would not be able to implement any
		      insertion or deletion of files */
	int nfile; /* This flag indicates if it is a new file */
	int rowoff; /* Row offset, to use for scrolling */
	char *next_stat_msg; /* Status message to be displayed next refresh */
	int status_mode; /* Whether we are getting input on the status bar */
	char *kill_buffer; /* Buffer to store cut or copied text */
	int cur_mode; /* current mode */
};

struct row {
	char *s;
	int size;
};

struct window win;
void init(char *name);

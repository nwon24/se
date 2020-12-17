struct window {
	int cx, cy;
	char *fname; /* file name */
	int nsaved;
	int ncol, nrow;
	struct row *rows;
	int numrows;
};

struct row {
	char *s;
	int size;
};

struct window win;
void init(char *name);

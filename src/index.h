#define WRITE(x)           fwrite(x, 1, strlen(x), stdout)
#define WRITELN(x)         puts(x);

#define REDIRECT(url)      WRITE("Location: ");puts(url)
#define SET_CONTENT_TEXT() WRITE("Content-type: text/plain\n")
#define SET_CONTENT_HTML() WRITE("Content-type: text/html\n")

#define END_CONTENT_TYPE() WRITE("\n")

#define WRITE_HEADER()     WRITE("<html>\n<head>")
#define WRITE_META()       WRITE("<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>\n<meta http-equiv='Content-Language' content='el'>")
#define BODY_START()       WRITE("<style type='text/css'>hr{height: 0px;border: 1px solid #006699;}</style></head>\n<body>")
#define BODY_END()         WRITE("</body>\n</html>")
#define TABLE_START()      WRITE("<table>")
#define TABLE_END()        WRITE("</table>")
#define ROW_START()        WRITE("<tr>")
#define ROW_END()          WRITE("</tr>\n")
#define CELL_START()       WRITE("<td>")
#define CELL_END()         WRITE("</td>")


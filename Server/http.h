char http_text_html[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: ";
char http_image_jpeg[] = "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: ";
char http_image_png[] = "HTTP/1.1 200 OK\r\nContent-Type: image/png\r\nContent-Length: ";
char http_image_gif[] = "HTTP/1.1 200 OK\r\nContent-Type: image/gif\r\nContent-Length: ";
static char * http_error =   "HTTP/1.0 404 Not Found\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  " <body>\n"
  "  <h1>Not Found</h1>\n"
  "  <p>The requested URL was not found on this server.</p>\n"
  " </body>\n"
  "</html>\n";
#ifndef PASTE_h
#define PASTE_H

enum PasteStyle {NEWLINE,SEQUENTIAL,SINGLE};
extern PasteStyle currentPasteStyle;
void pasteAll();

int newLineAllPaste();
int sequentialAllPaste();
int singleElementPaste();


#endif
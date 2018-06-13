#ifndef UTILS_H_
#define UTILS_H_

int HourDiff(char *time1, char *time2);
int get_file_size(FILE *fp);
int MoveFiles(char *oldname, char *newname);
void GetCurrentDateString(char *buf);
void GetCurrentDateTimeString(char *buf);
#endif /* UTILS_H_ */

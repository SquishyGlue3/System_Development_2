# מטלה 2 - גרפים והעמסת אופרטורים

במטלה הקודמת מימשתם את המחלקה `Graph.cpp` המאפשרת ייצוג של גרפים בעזרת מטריצת שכנויות. במטלה הזאת, אתם תרחיבו את המחלקה ותוסיפו תמיכה באופרטורים חשבוניים על גרפים.
כאמור, הגרפים מיוצגים בעזרת מטריצת שכנויות, לכן כל האופרטורים צריכים להיות חוקיים עבור מטריצות (כמו שלמדתם בקורס אלגברה לינאריתin this assignment i added a new methods to the graph class

Here are the new features that have been added to the Graph class. 

New Methods in Graph.cpp
getGraph(): Returns the current graph object.
getRowSum(): Returns the number of vertices (i.e., the sum of rows) in the graph.
getColSum(): Returns the number of vertices (i.e., the sum of columns) in the graph.
getEdgesNum(): Returns the number of edges in the graph.
operator+ (Graph &g1, Graph &g2): Overloads the + operator to add two graphs.
operator+= (Graph &g): Overloads the += operator to add another graph to the current graph.
operator+(): Overloads the unary + operator (empty implementation).
operator-(): Overloads the unary - operator to negate the adjacency matrix values.
operator- (Graph &g1, Graph &g2): Overloads the - operator to subtract one graph from another.
operator-= (Graph &g): Overloads the -= operator to subtract another graph from the current graph.
operator== (Graph &g1, Graph &g2): Overloads the == operator to compare two graphs for equality.
operator< (Graph &g1, Graph &g2): Overloads the < operator to compare two graphs.
operator<= (Graph &g1, Graph &g2): Overloads the <= operator to compare two graphs.
operator> (Graph &g1, Graph &g2): Overloads the > operator to compare two graphs.
operator>= (Graph &g1, Graph &g2): Overloads the >= operator to compare two graphs.
operator!= (Graph &g1, Graph &g2): Overloads the != operator to compare two graphs for inequality.
operator++(): Overloads the pre-increment operator to increment all edge values by one.
operator++(int): Overloads the post-increment operator to increment all edge values by one.
operator--(): Overloads the pre-decrement operator to decrement all edge values by one.
operator--(int): Overloads the post-decrement operator to decrement all edge values by one.
*operator (Graph &g1, Graph &g2)**: Overloads the * operator to multiply two graphs (matrix multiplication).
*operator (Graph &g, int scalar)**: Overloads the * operator to multiply a graph by a scalar.
operator<< (std::ostream &os, Graph &g): Overloads the << operator to print the graph.

אתם תצטרכו להוסיף את האופרטורים הבאים:

- שישה אופרטורים חשבוניים: חיבור (+) הוספה (+=) פלוס אונרי (+), ושלושת האופרטורים המקבילים לחיסור (-). כאמור, חיבור/חיסור של שתי מטריצות מוגדר רק על מטריצות מאותו סדר גודל nXn. ניסיון לחבר/לחסר שתי מטריצות שלא מקיימות תנאי זה יגרום לזריקת שגיאה.
- שישה אופרטורי השוואה: גדול, גדול-או-שווה, קטן, קטן-או-שווה, שווה, לא-שווה. לשם מטלה זו כללי השוואת גרפים הם כדלקמן:

  1. גרפים G1 ו-G2 ייקראו שווים אם הם מאותו סדר גודל ומכילים את אותן הצלעות (והמשקלים של הצלעות זהים) או אם G1 לא גדול מ-G2 וגם G2 לא גדול מ-G1.
  2. גרף G2 גדול מגרף G1 אם הגרף G1 מוכל ממש בגרף G2. אם אף גרף לא מוכל ממש בשני והגרפים לא שווים, אז גרף G2 גדול מגרף G1 אם מספר הצלעות ב-G2 גדול ממספר הצלעות ב-G1. אם בכל זאת מספר הצלעות זהה, אז הגרף G2 גדול מהגרף G1 אם המטריצה המייצגת של G2 בעלת סדר גודל גבוה יותר משל G1.

- הגדלה ב-1 (++) והקטנה ב-1 (--) לפני ואחרי המספר. פעולה זו תגדיל או תקטין ב-1 את כל המשקלים של הצלעות בגרף.
- הכפלה בסקלר שלם (`int`) - מכפיל את המשקל של כל הצלעות.
- הכפלת גרפים - אנחנו מגדירים את פעולת הכפל בין גרף G1 לגרף G2 על ידי מכפלה של המטריצות המייצגות של שני הגרפים. התוצאה צריכה להיות מטריצה המייצגת גרף. ניסיון לבצע כפל בין גרפים בגדלים שונים צריך לזרוק שגיאה.
- אופרטור פלט - הדפסה הגיונית של הגרף (צורת ההפדסה היא לשיקולכם).


כמו כן, עליכם לכלול גם את הקובץ `Algorithms.cpp` מהמטלה הקודמת ולראות כיצד הפונקציות שהגדרתם בפעם הקודמת משתנות עכשיו. בנוסף לקבצים של המטלה אתם נדרשים להגיש גם קובץ README המתאר את אופן המימוש ואת החלוקה שביצעתם בקוד (סוג של מדריך משתמש).
עליכם לכתוב בתחילת כל קובץ את מספר תעודת הזהות שלכם ואת המייל. אי עמידה בהנחיות תגרור הפחתה בציון.
בהצלחה!


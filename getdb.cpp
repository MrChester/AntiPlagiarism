#include <string>

#include <boost/variant.hpp>
#include <mysql.h>
#include <mysql_connection.h>

using namespace std;

const char server[] = "aws-plagiarism.cffzlwqqppj4.us-east-2.rds.amazonaws.com";
const char user[] = "admin";
const char password[] = "6wZ?osLan1hnS,7Q*M*!";
const char database[] = "TextAIDatabase";
const char sqlQuery[] = "SELECT EDocs.id, content FROM DocTypes JOIN EDocs ON DocTypes.id=EDocs.typeId WHERE name='dissertation' or name='scientific article';";

string getDb()
{
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    int qstate;
    string sumOfTexts = "";

    conn = mysql_init(NULL);

    if (conn != NULL) {
        conn = mysql_real_connect(conn, server, user, password, database, 3306, NULL, 0);
    }

    qstate = mysql_query(conn, sqlQuery);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        while (row)
        {
            sumOfTexts.append(" ");
            sumOfTexts.append(row[1]);

            row = mysql_fetch_row(res);
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return sumOfTexts;
}
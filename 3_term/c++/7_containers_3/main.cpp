#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QDebug>

// Aliases for readability
using Table = QMap<int, QMap<QString, int>>;

QVector<QVector<QString>> ReadTable(const QString& path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};

    QVector<QVector<QString>> rows;
    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QVector<QString> cols = line.split(';').toVector();
        rows.append(cols);
    }

    return rows;
}

Table ParseTable(const QString& filename)
{
    QVector<QVector<QString>> content = ReadTable(filename);
    if (content.isEmpty()) return {};

    Table buyList, available, demand;

    auto parse_table = [&](Table& table, int startCol = 0)
    {
        int col = 1 + startCol;

        for (; col < content.size() && !content[col][0].isEmpty(); col++)
        {
            for (int row = 1; row < content[col].size(); row++)
            {
                bool ok1, ok2;

                int room = content[0][row].toInt(&ok1);
                int val = content[col][row].toInt(&ok2);

                if (ok1 && ok2)
                    table[room][content[col][0]] = val;
            }
        }

        return col;
    };

    int afterAvailable = parse_table(available);
    parse_table(demand, afterAvailable + 1);

    for (int room : available.keys())
    {
        const QMap<QString, int>& furniture = available[room];

        for (const QString& name : furniture.keys())
        {
            int need = demand[room].value(name, 0) - furniture.value(name, 0);
            buyList[room][name] = qMax(need, 0);
        }
    }

    return buyList;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cin(stdin);
    QTextStream cout(stdout);

    QChar c = 'n';

    bool firstlyOpened = true;

    do
    {
        cout << "Enter a path to a file: " << Qt::flush;
        QString path = cin.readLine();

        Table buyList = ParseTable(path);

        if (buyList.isEmpty())
            cout << "Failed to parse a table or the file is empty.\n" << Qt::flush;
        else
        {
            //QString out;

            for (int room : buyList.keys())
            {
                cout << "Room " << room << ":\n" << Qt::flush;
                //out += QString("Room %1:\n").arg(room);

                for (const QString& name : buyList[room].keys())
                {
                    int count = buyList[room][name];
                    cout << "\t" << name << ": " << count << "\n" << Qt::flush;
                    //out += QString("\t%1: %2\n").arg(name).arg(count);
                }
            }

            cout << "Enter a room: " << Qt::flush;
            QString roomStr = cin.readLine();

            bool ok;
            int room = roomStr.toInt(&ok);

            if (!ok)
            {
                cout << "Invalid room number.\n" << Qt::flush;
                continue;
            }

            cout << "Enter a furniture title: " << Qt::flush;
            QString furnitureTitle = cin.readLine();

            if (!buyList.contains(room) || !buyList[room].contains(furnitureTitle))
                cout << "No such room or no such furniture in it\n" << Qt::flush;
            else
            {
                int demand = buyList[room][furnitureTitle];

                cout << "You need to buy " << demand << " " << furnitureTitle << "s\n" << Qt::flush;

                cout << "\nWould you like to save everything to a file (y/n)? " << Qt::flush;
                c = cin.readLine().at(0).toLower();

                if (c == 'y')
                {
                    QFile file("out.txt");

                    QIODeviceBase::OpenMode om = QIODevice::Text;

                    if (firstlyOpened)
                    {
                        om |= QIODevice::WriteOnly;
                        firstlyOpened = false;
                    }
                    else
                        om |= QIODevice::Append;

                    if (file.open(om))
                    {
                        QTextStream outStream(&file);
                        outStream << furnitureTitle << ": " << demand << Qt::endl;
                        file.close();
                    }
                }
            }
        }

        cout << "Would you like to rerun the program (y/n)? " << Qt::flush;
        c = cin.readLine().at(0).toLower();
    }
    while (c == 'y');

    return 0;
}

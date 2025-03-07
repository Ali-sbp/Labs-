#include <iostream>
#include "src/MyString.hpp"
/**
 * Лабораторная работа №2. Массивы объектов, простое наследование, виртуальные
 * функции, применение наследования.
 *
 * В этой работе и далее предполагается, что вы будете использовать классы,
 * написанные в прошлых работах, и дополнять их по необходимости. Эти классы
 * будут называться по имени без дополнительных указаний, что их надо взять из
 * прошлой работы.
 *
 * Предполагается, что новый классы будут созданы по аналогии с предыдущими
 * работами в отдельных файлах, которые будут включены в сборку.
 *
 * При работе с классами - в учебных целях - нельзя пользоваться контейнерами
 * стандартной библиотеки и нужно следовать принципам инкапсуляции.
 */

int main() {
    /**
     * Задание 1. Массивы объектов класса.
     */

    /**
     * Задание 1.1. Массив объектов.
     *
     * Объявите и проинициализируйте массив ar из объектов типа MyString.
     * Выведите элементы массива на консоль.
     */

    /* {
        MyString ar[3] = { ... };
        {
    MyString arr[3];
    for (int i=0 ; i<3 ; i++){
        arr[i]= "asd";
        //arr[i].print();
    }
    for (int i=0 ; i<3 ; i++){
        arr[i].print() ;
    }
}
    } */

    /**
     * Замените размер массива с 3 на 5, не меняя список инициализаторов.
     *
     * Чем были инициализированы последние 2 элемента? Какие значения могут
     * стоять в списке инициализаторов - в вашем случае и в общем случае?
     */
    /*
    {
    MyString arr[5];
    for (int i=0 ; i<3 ; i++){
        arr[i]= "asd";
        //arr[i].print();
    }
    for (int i=0 ; i<5 ; i++){
        arr[i].print() ;
    }
}
    output as expected :
    asd
    asd
    asd
    (null string)
    (null string)
    */

    /**
     * Задание 1.2. Массив указателей на объекты.
     *
     * Объявите и проинициализируйте массив arPtr из трех указателей на объекты
     * типа MyString. Выведите элементы массива на консоль.
     */
    
     //1-stack allocated
     {
    MyString a("First"), b("Second"), c("Third");
    MyString* arPtr[3] = {&a, &b, &c}; 

    for (int i = 0; i < 3; i++) {
        arPtr[i]->print();
    }
    }
    //2-dynamic 
    {
    MyString* arPtr[3];

    
    arPtr[0] = new MyString("First");
    arPtr[1] = new MyString("Second");
    arPtr[2] = new MyString("Third");

    for (int i = 0; i < 3; i++) {
        arPtr[i]->print(); 
    }

    //clean
    for (int i = 0; i < 3; i++) {
        delete arPtr[i];
    }
    }

    /**
     * Задание 2. Простое наследование. Аргументы конструктора, передаваемые в
     * базовый класс.
     */

    /**
     * Задание 2.1. Базовый класс.
     *
     * Создайте класс BaseFile, который будет реализовывать работу с файлами с
     * помощью стандартных средств C (cstdio).
     *
     * Класс должен иметь 3 конструктора: первый - конструктор по умолчанию,
     * второй должен принимать путь к файлу и параметры для открытия (как в
     * fopen), третий должен принимать готовый указатель FILE*.
     *
     * Считается, что этот класс *обладает* своим ресурсом - открытым файлом.
     * Что должно быть в дестукторе этого класса?
     *
     * Добавьте следующие методы:
     * - bool is_open() - возвращает true, если файл успешно открыт;
     * - bool can_read() - возвращает true, если из файла можно считать данные;
     * - bool can_write() - возвращает true, если в файл можно записать данные;
     * - size_t write_raw(const void *buf, size_t n_bytes) - записывает
     *   указанное количество байт в файл и возвращает количество байт, которое
     *   удалось записать;
     * - size_t read_raw(void *buf, size_t max_bytes) - читает доступные данные
     *   в буфер, но не более указанного количества и возвращает количество
     *   байт, которое удалось считать;
     * - long tell() - возвращает текущий сдвиг файла (см. функцию ftell);
     * - bool seek(long offset) - устанавливает сдвиг файла (см. функцию fseek)
     *   и возвращает true, если операция успешна.
     *
     * Добавьте также методы `read` и `write`, которые в этом классе будут
     * делать буквально то же, что `read_raw` и `write_raw`, они понадобятся нам
     * позже.
     *
     * Проверьте работу этого класса.
     */

    /**
     * Задание 2.2. Производные классы.
     *
     * Производный класс *наследуется* от базового класса и каким-то образом
     * расширяет его функциональность, при это все еще умея все, что умеет
     * базовый класс.
     *
     * Реализуйте следующие производные классы от класса BaseFile. Производные
     * классы нужно унаследовать так, чтобы пользователю были все еще доступны
     * методы базового класса. Каким образом нужно унаследовать класс для этого?
     * Как еще можно унаследовать класс?
     *
     * Производные классы могут располагаться в том же файле, где и базовый
     * класс.
     *
     * В производных классах добавьте необходимые конструкторы, которые будут
     * вызывать конструктор базового класса.
     *
     * Проверьте работу производных классов.
     */

    /**
     * Задание 2.2.1. Base32 кодировщик/декодировщик.
     *
     * Создайте производный класс Base32File, который будет проводить при
     * записи кодировку-декодировку данных, по алгоритму, который вы
     * реализовали в лабораторной работе №4 прошлого семестра.
     *
     * Переопределите методы `read` и `write`, которые будут проводить чтение из
     * файла с декодировкой и запись в файл с кодировкой соответственно.
     *
     * Добавьте возможность пользователю передать в конструктор таблицу
     * кодировки, по умолчанию используется таблица "A..Z1..6".
     */

    /**
     * Задание 2.2.2. RLE-сжатие.
     *
     * Создайте производный класс RleFile, который будет проводить побайтовое
     * сжатие при помощи алгоримта RLE (для простоты можно реализовать
     * неэффективный алгоритм, где последовательности без повторений отдельно
     * не кодируются).
     *
     * Переопределите методы `read` и `write`, которые будут проводить чтение из
     * файла с извлечением сжатой информации и запись в файл со сжатием
     * соответственно.
     *
     * Проверьте сжатие/извлечение на примере какого-нибудь ASCII-арта,
     * например, котенка из лабораторной №3 прошлого семестра. Посмотрите,
     * получилось ли добиться уменьшения размера хранимых данных.
     */

    /**
     * Задание 2.3. Конструкторы и деструкторы базового и производного классов.
     *
     * Установите отладочную печать в конструкторах и деструкторах каждого
     * класса из этого задания. Создайте локальные объекты производных классов,
     * отметьте, в каком порядке вызываются конструкторы и деструкторы при
     * инициализации и деинициализации этих классов.
     */

    /**
     * Задание 2.4. Ранее связывание.
     *
     * На основе данной заготовки напишите код, который запишет в файл строковое
     * представление целого числа. Вы должны использовать один и тот же код для
     * всех файлов, меняя только имя объекта (bf / b32f / rf), в который идет
     * запись.
     */

    /* {
        BaseFile bf(...);
        Base32File b32f(...);
        RleFile rf(...);

        int n = 123456;
        if (n < 0) { bf.write(...); }
        while (n > 0) {
            bf.write(...);
            // ...
        }

        n = 123456;
        if (n < 0) { b32f.write(...); }
        while (n > 0) {
            b32f.write(...);
            // ...
        }

        n = 123456;
        if (n < 0) { rf.write(...); }
        while (n > 0) {
            rf.write(...);
            // ...
        }

        {
    BaseFile bf("base.txt", "w");
    Base32File b32f("base32.txt", "w");
    RleFile rf("rle.txt", "w");

    // same code for bf
    int n = 123456;
    if (n < 0) { 
        const char minus = '-';
        bf.write(&minus, 1); 
        n = -n;
    }
    char digits[10]; // buffer for digits
    int len = 0;
    while (n > 0) {
        digits[len++] = '0' + (n % 10); // extract digits right to left
        n /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        bf.write(&digits[i], 1); // write digits left to right
    }

    // same code for b32f
    n = 123456;
    if (n < 0) { 
        const char minus = '-';
        b32f.write(&minus, 1); 
        n = -n;
    }
    len = 0;
    while (n > 0) {
        digits[len++] = '0' + (n % 10);
        n /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        b32f.write(&digits[i], 1);
    }

    // same code for rf
    n = 123456;
    if (n < 0) { 
        const char minus = '-';
        rf.write(&minus, 1); 
        n = -n;
    }
    len = 0;
    while (n > 0) {
        digits[len++] = '0' + (n % 10);
        n /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        rf.write(&digits[i], 1);
    }
    }
    } */

    /**
     * Задание 2.5. Передача объекта по ссылке / указателю.
     *
     * Прошлое задание выглядит странновато - зачем повторять код три раза?
     * Хорошо бы сделать функцию, которая примет объект файла и число, и
     * выполнит эти действия.
     *
     * Реализуйте функцию `write_int(BaseFile &file, int n)`, которая будет
     * принимать ссылку на файл и число, которое нужно будет напечатать.
     *
     * Принцип наследования предписывает, что везде, где можно использовать
     * базовый класс, можно использовать производный класс. Проверьте, можно
     * ли вызвать функцию, передав в нее объект класса Base32File и RleFile.
     *
     * Имеет ли вызов этой функции для производного класса тот же результат,
     * что и код, который вы написали выше? Почему?
     * 
     * 1-Can You Pass Base32File and RleFile?:
1-Yes, because they inherit from BaseFile and BaseFile& accepts any derived class.
2-Same Result as Task 2.4? Why?:
2-Yes, the output files are identical.
write is declared virtual in BaseFile. When file.write() is called, the runtime looks at the actual object type (BaseFile, Base32File, or RleFile) 
and calls the overridden version, not the base version. 
This is late binding (dynamic dispatch), enabled by the reference and virtual function.
     */

    /**
     * Задание 2.6. Виртуальные функции, позднее связывание.
     *
     * Объявите функции read и write в базовом классе *виртуальными*. Что это
     * означает? Как изменился размер объектов классов BaseFile, Base32File и
     * RleFile? Почему?
     *
     * Как изменилось поведение при вызове функции `write_int` для производных
     * классов? Почему?
     * 
     * SIZE IMPACT: 
     * 
     * 
     * Before (Non-Virtual):
    BaseFile: Just FILE* file (8 bytes on 64-bit) and bool owns_file (1 byte, padded to 8 bytes) → ~16 bytes (depends on padding).
    Base32File: Adds char encoding_map[32] → ~48 bytes.
    RleFile: No extra data → ~16 bytes.
    After (Virtual):
    Adding virtual introduces a vtable pointer (typically 8 bytes on 64-bit systems) to each object that has virtual functions.
    New sizes:
    BaseFile: ~24 bytes (file + owns_file + vtable pointer).
    Base32File: ~56 bytes (base + encoding_map + vtable pointer).
    RleFile: ~24 bytes (base + vtable pointer).
    Why: The vtable pointer stores the address of a table mapping virtual functions to their implementations. 
    Every object of a class with virtual functions gets this extra pointer, increasing size.

    BEHAVIOUR: 
    2.4 : Early binding : bf.write() ... are called directly on objects of known type
          compiler picked the write function at compile time (early binding)
          each function wrote: 11123456 (in their own way: normal , 32, Rle)
    2.5: with virtual table 
          the runtime checks objects type :
          BaseFile bf; write_int(bf, 11123456) >> BaseFile::write (raw)
          Base32File b32f; write_int(b32f, 11123456) >> Base32File::write (Base32)
          RleFile rf; write_int(rf, 11123456) >> RleFile::write (RLE)

    this has same results but different mechanics :  

    2.4 : static calls
    2.5 : uses dynamic dispatch via Vtable


     */

    /**
     * Задание 2.7. Виртуальный деструктор.
     *
     * В следующем блоке кода добавьте удаление динамической памяти.
     *
     * Какой деструктор при этом вызывается? Почему? К каким проблемам это может
     * привести?
     *
     * Исправьте эту ситуацию.
     */

    /* {
        BaseFile *files[] = { 
            new BaseFile(...), 
            new RleFile(...), 
            new Base32File(...), 
        };

        for (int i = 0; i < 3; ++i) {
            files[i]->write("Hello!", 6);
        }
            for (int i = 0; i < 3; ++i) {
        delete files[i];
    } */

    /*
        1) without virtual destructor:
        if no virtual destructor in BaseFile (parent class) >> only ~BaseFile() is called cause of early binding. (no Vtable lookup occurs)
        because of this neither ~Base32File() nor ~RleFile() are called and any specefic derived class resources are skipped! (here it leaks memory on files[1], files[2] 
        because their respective destructors are not called)
        2)fixing: 
        virtual ~BaseFile();  (only in BaseFile.hpp) so instead of early binding we get late binding and Vtable is formed. and respective destructors will be called. 

    */

    /**
     * Задание 2.8. Массив объектов производных классов.
     *
     * Раскомментируйте следующий блок и объясните, почему:
     * а) не возникает ошибок при компиляции;
     * б) возникают ошибки при выполнении.
     *
     * Этот пример показывает очень плохую практику, которая приводит к ошибкам;
     * для создания массива объектов производного класса и используйте массив
     * указателей на базовый класс, как это было сделано выше. Реализуйте ту же
     * логику, используя массив указателей на объекты базового класса.
     */

    /* {
        BaseFile *base_files = new BaseFile[2] { BaseFile(...), BaseFile(...) };
        BaseFile *b32_files = new Base32File[2] { Base32File(...), Base32File(...) };
        for (int i = 0; i < 2; ++i) {
            base_files[i].write("Hello!", 6);
            b32_files[i].write("Hello!", 6);
        }
        delete [] base_files;
        delete [] b32_files;
    } */
        /*
        а) не возникает ошибок при компиляции? 
            1- syntax is correct so it compiles.
        б) возникают ошибки при выполнении?
            1- in this fragment: "BaseFile *b32_files = new Base32File[2]" we are making an array of objects of BaseFile32 but assigning it to a BaseFile type. 
             the pointer arithmetic assumes each element is the size of a BaseFile (24 bytes with vtable) not a Base32File (56 bytes due to encoding_map[32]).
             Result: b32_files[1] points to garbage memory within the first Base32File object, not the second object.

        corrected version: 
        {
    BaseFile** files = new BaseFile*[2];
    files[0] = new BaseFile("base.txt", "w");
    files[1] = new Base32File("base32.txt", "w");

    for (int i = 0; i < 2; ++i) {
        files[i]->write("Hello!", 6);
    }

    for (int i = 0; i < 2; ++i) {
        delete files[i];
    }
    delete[] files;
    }
        */
    /**
     * Задание 3. Чисто виртуальные функции. Интерфейсы. Композиция классов.
     *
     * Наследование позволяет довольно просто переиспользовать данные и логику
     * других классов, однако зачастую этот механизм недостаточно гибкий для
     * полноценного переиспользования.
     *
     * Например, сможем ли мы в получившейся иерархии классов реализовать
     * одновременно и кодирование в base32, и сжатие при записи данных в файл?
     * Или сможем ли мы вместо записи в файл на диске делать запись в строковый
     * буфер в памяти?
     *
     * При дальнейшем рассмотрении окажется, что при помощи наследования мы
     * крепко *связали* логику преобразования данных с записью в конкретный
     * файл. Далее мы рассмотрим один из способов разделения такой логики.
     */

    /**
     * Задание 3.1. Абстрактный базовый класс, чисто виртуальные функции.
     *
     * Первая проблема в нашей реализации - все наследники BaseFile будут всегда
     * обязаны непосредственно писать в файл на диске. Чтобы избавиться от этой
     * необходимости, стоит сделать базовый класс *абстрактным* в том смысле,
     * что у него не будет полей связанных с конкретным способом писать в файл.
     *
     * Создайте класс `IFile`, в котором не будет полей, но будут методы
     * `can_read`, `can_write`, `read` и `write` с такими же сигнатурами, как и
     * классе `BaseFile`. Что именно будут делать эти методы? Класс `IFile` не
     * может знать, поскольку логику этих методов будут определять наследники.
     * В этом классе эти методы не имеют реализации, и они должны быть объявлены
     * *чисто виртуальными*.
     *
     * Какие ограничения накладывает на класс наличие чисто виртуального метода?
     * 
     * ANSWER:  IFile is abstract—can’t instantiate it (IFile f; fails)
                Derived classes must override all pure virtual methods, or they’re abstract too
     *
     * Получается, что в классе `IFile` есть только чисто виртуальные методы, и
     * единственная цель такого класса - определять, что должны уметь делать его
     * наследники. Совокупность действий, которые можно сделать с объектом,
     * называется его *интерфейсом*, и такие классы тоже часто называются
     * интерфейсами, отсюда берется приставка "I" в имени класса.
     *
     * Унаследуйте класс `BaseFile` от класса `IFile` и измените функцию
     * `write_int`, чтобы она работала с произвольным наследником `IFile`.
     *
     * Убедитесь, что в программе выше ничего не сломалось.
     */

    /**
     * Задание 3.2. Композиция вместо наследования.
     *
     * Реализуйте классы `Base32File2` и `RleFile2`, которые будут унаследованы
     * от класса `IFile` и в конструкторе будут получать другой объект `IFile`,
     * чьи функции они будут использовать вместо функций базового класса.
     *
     * Объекты получают объект `IFile` в виде указателя на динамически
     * выделенную память, и они ответственны за ее очищение.
     *
     * Использование объектом другого объекта в качестве поля называется
     * *композицией*.
     *
     * Проверьте, что используемые ниже объекты работают так же, как объекты
     * классов `Base32File` и `RleFile`.
     */

    /* {
        Base32File2 b32f(new BaseFile(...));
        RleFile2 rf(new Base32File(...));
        write_int(b32f, 123456);
        write_int(rf, 123456);
    } */

    /**
     * Задание 3.3. Больше композиции!
     *
     * Не реализовывая больше никаких классов, соорудите объект-наследник IFile,
     * который будет при вызове метода `write` два раза кодировать в base32,
     * после чего применять сжатие RLE и только после этого писать в файл.
     */

    /*{
        {
            RleFile2 rf(new Base32File2(new Base32File2(new BaseFile("../tests/output33.txt", "w"))));
            
            
            write_int(rf, 123456);
        }
    }*/

    return 0;
}

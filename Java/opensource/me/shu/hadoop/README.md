### Hadoop - [WordCount](http://www.cloudera.com/content/cloudera-content/cloudera-docs/HadoopTutorial/CDH4/Hadoop-Tutorial/ht_wordcount1.html)

- usage
    - create directory

            hadoop fs -mkdir /user/hduser/wordcount /user/hduser/wordcount/input

    - generate data

            echo "Hello World Bye World" > file0
            echo "Hello Hadoop Goodbye Hadoop" > file1
            hadoop fs -put file* /user/hduser/wordcount/input

    - generate jar file

            mkdir wordcount_classes
            javac -cp /usr/local/hadoop-2.2.0/share/hadoop/hdfs/*:/usr/local/hadoop-2.2.0/share/hadoop/common/*:/usr/local/hadoop-2.2.0/share/hadoop/mapreduce/*:/usr/local/hadoop-2.2.0/share/hadoop/yarn/* -d wordcount_classes org/myorg/WordCount.java
            jar -cvf wordcount.jar -C wordcount_classes/ .

    - execute mapreduce

            hadoop jar wordcount.jar org.myorg.WordCount /user/hduser/wordcount/input /user/hduser/wordcount/output

    - check output

            hadoop fs -cat /user/hduser/wordcount/output/part-00000

    - clean output

            hadoop fs -rm -r /user/hduer/wordcount/output

Scala学习总结
=====

[sbt学习总结](http://www.scala-sbt.org/0.13/tutorial/zh-cn/index.html)
-----

### 安装

从官方网站[下载链接](http://www.scala-sbt.org/download.html)下载Windows安装包，**安装路径不要包含空格**。

在任何目录下运行 `sbt` 命令进入 `sbt REPL`。

### 目录结构

在 sbt 的术语里，“基础目录”是包含项目的目录，sbt 的源文件目录结构如下所示， 和 maven 的目录结构相同。
```
build.sbt
project/
  build.scala
src/
  main/
    resources/
       <files to include in main jar here>
    scala/
       <main Scala sources>
    java/
       <main Java sources>
  test/
    resources
       <files to include in test jar here>
    scala/
       <test Scala sources>
    java/
       <test Java sources>
```
基础目录中有 build.sbt，project 目录可以包含 .scala 文件，这些文件最后会和 .sbt 文件合并共同构成完整的构建定义。

 .gitignore 文件（或者其他版本控制系统等同的文件）应该包含`target/`。注意：这里后面需要跟一个 / （只匹配目录）且前面不能有 / （除了匹配普通的`target/`还匹配`project/target/`）。
 
### 运行
 
可以以空格为分隔执行多个sbt命令，对于接受参数的 sbt 命令，将命令和参数用引号引起来一起传给 sbt。如`sbt clean compile "testOnly TestA TestB"`，sbt会按顺序执行（clean， compile， 然后 testOnly）。

在命令前面加上前缀 ~后，每当有一个或多个源文件发生变化时就会自动运行该命令。例如，在交互模式下尝试 `~ compile`，按回车键停止监视变化。你可以在交互模式或者批处理模式下使用 ~ 前缀。

### 常见命令
常用命令 

下面是一些非常常用的的 sbt 命令。更加详细的列表请参见[命令行参考](http://www.scala-sbt.org/0.13/tutorial/docs/Command-Line-Reference.html)。

|  命令      |  描述    |
| ----------      | -----    |
| clean     | 	删除所有生成的文件 （在 target 目录下）。|
| compile   |	编译源文件（在 src/main/scala 和 src/main/java目录下）。|
| test      | 	编译和运行所有测试。|
| console   | 	进入到一个包含所有编译的文件和所有依赖的classpath 的 Scala 解析器。输入:quit，Ctrl+D（Unix），或者Ctrl+Z（Windows） 返回到 sbt。|
| run       |	在和sbt所处的同一个虚拟机上执行项目的mainclass。|
| package   |	将src/main/resources下的文件和src/main/scala以及src/main/java 中编译出来的 class 文件打包成一个 jar 文件。|
| help      |	显示指定的命令的详细帮助信息。如果没有指定命令，会显示所有命令的简介。|
| reload    |	重新加载构建定义（build.sbt，project/*.scala，project/*.sbt这些文件中定义的内容)。在修改了构建定义文件之后需要重新加载。|

### sbt定义文件

build.sbt是一个以**空行分隔**的Scala表达式的列表。它们仅仅是表达式，不是完整的 Scala 语句，这些表达式可以用 val，lazy val，def 声明。

### 依赖

#### [eclipse插件](https://github.com/typesafehub/sbteclipse)

有2种配置方式：

- 在~/.sbt/0.13/plugins/build.sbt里配置
- 在每个项目的project/plugins.sbt里配置。

添加`addSbtPlugin("com.typesafe.sbteclipse" % "sbteclipse-plugin" % "2.5.0")`，然后运行`sbt eclipse`命令生成eclipse工程文件。

在build.sbt文件里添加`EclipseKeys.createSrc := EclipseCreateSrc.Default + EclipseCreateSrc.Resource`以生成资源文件目录`resources`

### 多项目
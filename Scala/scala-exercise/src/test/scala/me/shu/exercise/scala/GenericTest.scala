package me.shu.exercise.scala

class Reference[T] {
  private var contents: T = _
  def set(value: T) { contents = value }
  def get: T = contents
}

object GenericTest {
  def main(args: Array[String]) {
    val cell = new Reference[Int]
    cell.set(13)
    println("Reference contains the half of " + (cell.get * 2))
  }
}
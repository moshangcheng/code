package me.shu.exercise.drools.basic.join;

public class Item {

	private double score;

	private double price;

	public Item(double score, double price) {
		super();
		this.score = score;
		this.price = price;
	}

	public double getScore() {
		//System.out.println("score@" + this + " is " + score);
		return score;
	}

	public void setScore(double score) {
		this.score = score;
	}

	public double getPrice() {
		//System.out.println("price@" + this + " is " + price);
		return price;
	}

	public void setPrice(double price) {
		this.price = price;
	}

}

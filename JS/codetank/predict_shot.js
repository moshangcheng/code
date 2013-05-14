/**    
 * CODETANK 
 * Copyright (c) 2012, Tencent AlloyTeam, All rights reserved.
 * http://CodeTank.AlloyTeam.com/
 *
 * @version     1.0
 * @author      moshangcheng
 *
 *  .d8888b.                888      88888888888               888   TM   
 * d88P  Y88b               888      ''''888''''               888      
 * 888    888               888          888                   888      
 * 888         .d88b.   .d88888  .d88b.  888  8888b.  88888b.  888  888 
 * 888        d88""88b d88" 888 d8P  Y8b 888     "88b 888 "88b 888 .88P 
 * 888    888 888  888 888  888 88888888 888 .d888888 888  888 888888K  
 * Y88b  d88P Y88..88P Y88b 888 Y8b.     888 888  888 888  888 888 "88b 
 *  "Y8888P"   "Y88P"   "Y88888  "Y8888  888 "Y888888 888  888 888  888 
 * 
 */

Jx().$package(function(J){
    
    //智能巡逻
    var patrol = {
        aroundMap: function(t) {
            //调整角度
            t.turnLeft(t.getMinAngle(t.getHeading(), 0), function(){
        		//沿着墙壁绕圈
				t.ahead(t.getBattleFieldWidth() - t.getX() - t.DiagonalLength / 2.0, function() {
					t.turnLeft(90);
					t.ahead(t.getY() - t.DiagonalLength / 2.0, function() {
						t.turnLeft(90);
						t.ahead(t.getX() - t.DiagonalLength / 2.0, function() {
							t.turnLeft(90);
							t.ahead(t.getBattleFieldHeight() - t.getY() - t.DiagonalLength / 2.0, function() {
								t.turnLeft(90);
								t.ahead(t.getBattleFieldWidth() - t.getX() - t.DiagonalLength / 2.0);
							});
						});
					});
				});
			});
        },
		
		goToCentral: function(t) {
			t.turnLeft(t.getMinAngle(t.getHeading(), 0));
			t.ahead(t.getBattleFieldWidth() / 2.0 - t.getX(), function(){
				t.turn(90);
				t.ahead(t.getBattleFieldHeight() / 2.0 - t.getY());
			});
		}
    };
    
    Robot = new J.Class({extend : tank.Robot},{
		/**
		*robot主循环
		**/	
        
        DELTA: 0.01,
		
		getMinAngle: function(angleA, angleB){
            var angleToTurn = angleB - angleA;        
            while(angleToTurn > 180) {
                angleToTurn -= 360;
            }
            while(angleToTurn < -180) {
                angleToTurn += 360;
            }
			return angleToTurn;
        },
		
		
        
		run:function(){
            this.DiagonalLength = Math.sqrt(this.getWidth() * this.getWidth() + this.getHeight() * this.getHeight());
			this.setAdjustGunForRobotTurn(true);
    		this.setAdjustRadarForGunTurn(false);
			patrol.goToCentral(this);
			this.loop(function(){
				this.turnGunLeft(10);
			});
		},

		/**
		*看到其他robot的处理程序
		**/
		onScannedRobot:function(e){
    		this.say("就是干");
			//获得相对角度
			var relativeAngle = e.getBearing() + this.getHeading();
			console.log(e.getSpeed() + ", " + this.getSpeed() + ", *****" + relativeAngle);
			var bulletFlyTime = e.getDistance() / 12.0;
			var deltaX = e.getSpeed() * Math.cos(e.getHeading() * Math.PI / 180) * bulletFlyTime;
			var deltaY = e.getSpeed() * Math.sin(e.getHeading() * Math.PI / 180) * bulletFlyTime;
			console.log(deltaX + "," + deltaY);
			var angleToTurn = 0;
			if(Math.abs(deltaX) > this.DELTA || Math.abs(deltaY) > this.DELTA) {
				deltaX += e.getDistance() * Math.cos(relativeAngle * Math.PI / 180);
				deltaY += e.getDistance() * Math.sin(relativeAngle * Math.PI / 180);
				console.log(deltaX + "," + deltaY);
				angleToTurn = Math.atan(deltaX / deltaY) / Math.PI * 180;
				if(Math.abs(deltaX) < this.DELTA) {
					if(deltaY > 0) {
						angleToTurn = 90;
					} else {
						angleToTurn = 270;
					}
				} else if(Math.abs(deltaY) < this.DELTA) {
					if(deltaX > 0) {
						angleToTurn = 0;
					} else {
						angleToTurn = 180;
					}
				} else if(deltaX * deltaY < 0) {
					if(deltaX > 0) {
						angleToTurn = 360 + angleToTurn;
					} else {
						angleToTurn = 180 + angleToTurn;
					}
				} else {
					if(deltaX < 0) {
						angleToTurn = 180 + angleToTurn;
					}
				}
				angleToTurn -= relativeAngle;
			}
			console.log(angleToTurn);
			this.turnGunLeft(this.getMinAngle(this.getGunHeading(), this.getHeading() + e.getBearing() + angleToTurn), function(){
				this.fire(3);
				this.scan();
			});
		},

		/**
		*被子弹击中的处理程序
		**/
		onHitByBullet:function(e){
			this.say("谁打我，我打谁");
		},

		/**
		*和墙碰撞的处理程序
		**/
		onHitWall:function(e){
			this.say("这不可能");
		},

		onRobotDeath:function(e){
			this.say("我死了，连羽毛也腐烂在土地里面");
		}
	});
});
﻿/**    
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

    var patrol = {
        aroundMap: function(t) {
            t.turn(-1.0 * t.getMinAngle(t.getHeading(), 0), function(){
    			t.ahead(t.getBattleFieldWidth() - t.getX() - t.DiagonalLength / 2.0, function() {
					t.turn(-1.0 * t.getMinAngle(t.getHeading(), 90), function(){
						t.ahead(t.getY() - t.DiagonalLength / 2.0, function() {
							t.turn(-1.0 * t.getMinAngle(t.getHeading(), 180), function() {
								t.ahead(t.getX() - t.DiagonalLength / 2.0, function() {
									t.turn(-1.0 * t.getMinAngle(t.getHeading(), 270), function() {
										t.ahead(t.getBattleFieldHeight() - t.getY() - t.DiagonalLength / 2.0, function() {
											patrol.aroundMap(t);
										});
									});
								});
							});
						});
					});
				});
			});
        },
		
		goToCentral: function(t) {
			t.turn(-1.0 * t.getMinAngle(t.getHeading(), 0), function() {
				t.ahead(t.getBattleFieldWidth() / 2.0 - t.getX(), function(){
					t.turn(-1.0 * t.getMinAngle(t.getHeading(), 90), function(){
						t.ahead(t.getY() - t.getBattleFieldHeight() / 2.0);
					});
				});
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
			patrol.aroundMap(this);
			this.loop(function(){
				this.turnGunLeft(10);
			});
		},

		/**
		*看到其他robot的处理程序
		**/
		onScannedRobot:function(e){
    		this.say("就是干");
			this.turnGunLeft(this.getMinAngle(this.getGunHeading(), this.getHeading() + e.getBearing()));
			if(this.getGunHeat() == 0) {
				this.fire(3);
			}
			this.scan();
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
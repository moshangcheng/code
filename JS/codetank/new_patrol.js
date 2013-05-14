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
            t.setTurn(-1.0 * t.getMinAngle(t.getHeading(), 0), function(){
    			t.setAhead(t.getBattleFieldWidth() - t.getX() - t.DiagonalLength / 2.0, function() {
					t.setTurn(-1.0 * t.getMinAngle(t.getHeading(), 90), function(){
						t.setAhead(t.getY() - t.DiagonalLength / 2.0, function() {
							t.setTurn(-1.0 * t.getMinAngle(t.getHeading(), 180), function() {
								t.setAhead(t.getX() - t.DiagonalLength / 2.0, function() {
									t.setTurn(-1.0 * t.getMinAngle(t.getHeading(), 270), function() {
										t.setAhead(t.getBattleFieldHeight() - t.getY() - t.DiagonalLength / 2.0, function() {
											patrol.aroundMap(t);
										});
									});
								});
							});
						});
					});
				});
			});
        }
    };
	
	var radar = {
		sts : true,
		search : function(t) {
			if(radar.sts) {
				t.turnGunLeft(10, function(){
					radar.search(t);
				});
			} else {
				patrol.aroundMap(t);
			}
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
			//radar.search(this);
            //patrol.aroundMap(this);
            console.log(this.stopMove);
			this.loop(function(){
                JSON.stringify(this);
				this.turnGunLeft(10);
                //this.execute();
			});
		},

		/**
		*看到其他robot的处理程序
		**/
		onScannedRobot:function(e){
    		this.say("就是干");
			this.turnGunLeft(this.getMinAngle(this.getGunHeading(), this.getHeading() + e.getBearing()));
            this.say(console.log(this.getGunHeat() + ", " + this.getGunColdRate()));
			this.fire(3);
            this.say(console.log(this.getGunHeat() + ", " + this.getGunColdRate()));
			this.scan();
            if(radar.sts) {
        	    patrol.aroundMap(this);   
			}
			radar.sts = false;
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
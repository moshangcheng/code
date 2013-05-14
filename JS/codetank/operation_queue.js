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

    var patrol = {
        aroundMap: function(t) {
            //调整角度
            t.myTurn(t.getMinAngle(t.getHeading(), 0), function(){
        		//沿着墙壁绕圈
				t.myAhead(t.getBattleFieldWidth() - t.getX() - t.DiagonalLength / 2.0, function() {
					t.myTurn(90);
					t.myAhead(t.getY() - t.DiagonalLength / 2.0, function() {
						t.myTurn(90);
						t.myAhead(t.getX() - t.DiagonalLength / 2.0, function() {
							t.myTurn(90);
							t.myAhead(t.getBattleFieldHeight() - t.getY() - t.DiagonalLength / 2.0, function() {
								t.myTurn(90);
								t.myAhead(t.getBattleFieldWidth() - t.getX() - t.DiagonalLength / 2.0);
							});
						});
					});
				});
			});
        },
		
		goToCentral: function(t) {
			t.myTurn(t.getMinAngle(t.getHeading(), 0), function(){
				t.myAhead(t.getBattleFieldWidth() / 2.0 - t.getX(), function(){
					t.myTurn(90, function(){
						t.myAhead(t.getY() - t.getBattleFieldHeight() / 2.0);
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
		
		ROTATE_SPEED: 10 * 6,
		
		TANK_SPEED: 10 * 8,
		
		BULLET_SPEED: 12,
		
		turnQueue: [],
		gunTurnQueue: [],
		radarTurnQueue: [],
		aheadQueue: [],
		firePower: 0,
		
		
		myTurn: function(p, f) {
			this.turnQueue.push({p: p, f: f});
		},
		
		myGunTurn: function(p, f) {
			this.gunTurnQueue.push({p: p, f: f});
		},
		
		myRadarTurn: function(p, f) {
			this.radarTurnQueue.push({p: p, f: f});
		},
		
		myAhead: function(p, f) {
			this.aheadQueue.push({p: p, f: f});
		},
		
		myFire: function(p) {
			this.firePower = p;
		},
		
		atom: function() {
			if(this.turnQueue.length > 0) {
				var op = this.turnQueue[0];
				var sig = op.p > 0 ? 1 : -1;
				if(Math.abs(op.p) < this.ROTATE_SPEED) {
					this.setTurn(-1.0 * op.p);
					if(op.f != undefined) op.f.call(this);
					this.turnQueue.shift();
				} else {
					this.setTurn(-1.0 * sig * this.ROTATE_SPEED);
					op.p -= sig * this.ROTATE_SPEED;
				}
			}
			
			if(this.gunTurnQueue.length > 0) {
				var op = this.gunTurnQueue[0];
				var sig = op.p > 0 ? 1 : -1;
				if(Math.abs(op.p) < this.ROTATE_SPEED) {
					this.setGunTurn(op.p);
					if(op.f != undefined) op.f.call(this);
					this.gunTurnQueue.shift();
				} else {
					this.setGunTurn(sig * this.ROTATE_SPEED);
					op.p -= sig * this.ROTATE_SPEED;
				}
			}
			
			if(this.radarTurnQueue.length > 0) {
				var op = this.radarTurnQueue[0];
				var sig = op.p > 0 ? 1 : -1;
				if(Math.abs(op.p) < this.ROTATE_SPEED) {
					this.setRadarTurn(op.p);
					if(op.f != undefined) op.f.call(this);
					this.radarTurnQueue.shift();
				} else {
					this.setRadarTurn(sig * this.ROTATE_SPEED);
					op.p -= sig * this.ROTATE_SPEED;
				}
			}
			
			if(this.aheadQueue.length > 0) {
				var op = this.aheadQueue[0];
				var sig = op.p > 0 ? 1 : -1;
				if(Math.abs(op.p) < this.TANK_SPEED) {
					this.setAhead(op.p);
					if(op.f != undefined) op.f.call(this);
					this.aheadQueue.shift();
				} else {
					this.setAhead(sig * this.TANK_SPEED);
					op.p -= sig * this.TANK_SPEED;
				}
			}
			
			if(this.firePower > 0) {
				flag = true;
				this.fire(this.firePower);
				this.firePower = 0;
			}
			this.execute();
		},
		
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
			//this.setAdjustGunForRobotTurn(true);
    		//this.setAdjustRadarForGunTurn(false);
			patrol.aroundMap(this);
			this.loop(function(){
				this.atom();
			});
		},

		/**
		*看到其他robot的处理程序
		**/
		onScannedRobot:function(e){
    		this.say("就是干");
			this.myTurn(this.getMinAngle(this.getGunHeading(), this.getHeading() + e.getBearing()), function(){
				this.myFire(3);
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
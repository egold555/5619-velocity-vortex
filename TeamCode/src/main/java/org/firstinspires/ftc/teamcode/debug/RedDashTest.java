package org.firstinspires.ftc.teamcode.debug;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.eventloop.opmode.TeleOp;

import org.redshiftrobotics.reddash.RedDash;


@TeleOp(name = "RedDash", group = "Debug")
public class RedDashTest extends OpMode {

	@Override
	public void init() {
	}

	@Override
	public void start() {
		RedDash.set("Test", "It Works");
	}

	@Override
	public void stop() {
	}

	@Override
	public void loop() {
		RedDash.set("X Pressed", gamepad1.x ? "Yes" : "No");

		try {
			Thread.sleep(500, 0);
		} catch (InterruptedException e) {
			// Ignore
		}
	}
}

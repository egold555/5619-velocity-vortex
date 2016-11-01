package org.firstinspires.ftc.teamcode.debug;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.eventloop.opmode.TeleOp;

import org.redshiftrobotics.reddash.RedDash;
import org.redshiftrobotics.reddash.RedDashOpMode;


@TeleOp(name = "RedDash", group = "Debug")
public class RedDashTest extends RedDashOpMode {
	private int i = 0;

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
//		telemetry.addLine("Test line");
//		telemetry.addData("Answer", 42);
//		telemetry.addData("Ari is the", "King");
		telemetry.addData("Count", i++);
		telemetry.update();

		try {
			Thread.sleep(500, 0);
		} catch (InterruptedException e) {
			// Ignore
		}
	}
}

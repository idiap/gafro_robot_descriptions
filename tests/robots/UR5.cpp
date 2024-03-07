#include <catch.hpp>
#include <gafro/gafro.hpp>

using namespace gafro;

TEST_CASE("UR5", "[UR5]")
{
    UR5<double> robot;

    SECTION("Random configuration")
    {
        auto config = robot.getRandomConfiguration();

        REQUIRE(config.rows() == 6);
        REQUIRE(config.cols() == 1);
    }

    SECTION("Joint limits")
    {
        SECTION("Get min limits")
        {
            const Eigen::Matrix<double, 6, 1> &limitsMin = robot.getSystem().getJointLimitsMin();

            REQUIRE(limitsMin(0, 0) == Approx(-6.28319));
            REQUIRE(limitsMin(1, 0) == Approx(-6.28319));
            REQUIRE(limitsMin(2, 0) == Approx(-6.28319));
            REQUIRE(limitsMin(3, 0) == Approx(-6.28319));
            REQUIRE(limitsMin(4, 0) == Approx(-6.28319));
            REQUIRE(limitsMin(5, 0) == Approx(-6.28319));
        }

        SECTION("Get max limits")
        {
            const Eigen::Matrix<double, 6, 1> &limitsMax = robot.getSystem().getJointLimitsMax();

            REQUIRE(limitsMax(0, 0) == Approx(6.28319));
            REQUIRE(limitsMax(1, 0) == Approx(6.28319));
            REQUIRE(limitsMax(2, 0) == Approx(6.28319));
            REQUIRE(limitsMax(3, 0) == Approx(6.28319));
            REQUIRE(limitsMax(4, 0) == Approx(6.28319));
            REQUIRE(limitsMax(5, 0) == Approx(6.28319));
        }
    }

    SECTION("configuration 1")
    {
        Eigen::Vector<double, 6> configuration({ 0.5, -0.3, 0.0, -1.8, 0.0, 1.5 });

        Motor<double> ee_motor = robot.getEEMotor(configuration);

        Point<double> point(0.0, 0.0, 0.0);

        Point<double> ee_point = ee_motor.apply(point);

        REQUIRE(ee_point.get<blades::e0>() == Approx(1.0));
        REQUIRE(ee_point.get<blades::e1>() == Approx(0.1918632812));
        REQUIRE(ee_point.get<blades::e2>() == Approx(0.3229715006));
        REQUIRE(ee_point.get<blades::e3>() == Approx(0.8221240619));
        REQUIRE(ee_point.get<blades::ei>() == Approx(0.408505041));
    }

    SECTION("configuration 2")
    {
        Eigen::Vector<double, 6> configuration({ -0.5, -0.3, 0.0, -1.8, 0.0, 1.5 });

        Motor<double> ee_motor = robot.getEEMotor(configuration);

        Point<double> point(0.0, 0.0, 0.0);

        Point<double> ee_point = ee_motor.apply(point);

        REQUIRE(ee_point.get<blades::e0>() == Approx(1.0));
        REQUIRE(ee_point.get<blades::e1>() == Approx(0.3754353199));
        REQUIRE(ee_point.get<blades::e2>() == Approx(0.0130548624));
        REQUIRE(ee_point.get<blades::e3>() == Approx(0.8221240619));
        REQUIRE(ee_point.get<blades::ei>() == Approx(0.408505041));
    }

    SECTION("inverse dynamics 1")
    {
        Eigen::Vector<double, 6> position({ 0.680375, -0.211234, 0.566198, 0.59688, 0.823295, -0.604897 });
        Eigen::Vector<double, 6> velocity({ 0.536459, -0.444451, 0.10794, -0.0452059, 0.257742, -0.270431 });
        Eigen::Vector<double, 6> acceleration({ 0.904459, 0.83239, 0.271423, 0.434594, -0.716795, 0.213938 });

        Eigen::Vector<double, 6> torque = robot.getJointTorques(position, velocity, acceleration);

        REQUIRE(torque[0] == Approx(0.932673));
        REQUIRE(torque[1] == Approx(7.69722));
        REQUIRE(torque[2] == Approx(-3.88589));
        REQUIRE(torque[3] == Approx(0.303155));
        REQUIRE(torque[4] == Approx(-0.0102582));
        REQUIRE(torque[5] == Approx(0.0339077));
    }

    SECTION("inverse dynamics 2")
    {
        Eigen::Vector<double, 6> position({ 0.997849, -0.563486, 0.0258648, 0.678224, 0.22528, -0.407937 });
        Eigen::Vector<double, 6> velocity({ 0.0485744, -0.012834, 0.94555, -0.414966, 0.542715, 0.05349 });
        Eigen::Vector<double, 6> acceleration({ -0.199543, 0.783059, -0.433371, -0.295083, 0.615449, 0.838053 });

        Eigen::Vector<double, 6> torque = robot.getJointTorques(position, velocity, acceleration);

        REQUIRE(torque[0] == Approx(0.0825726));
        REQUIRE(torque[1] == Approx(33.5392));
        REQUIRE(torque[2] == Approx(8.77025));
        REQUIRE(torque[3] == Approx(0.0112162));
        REQUIRE(torque[4] == Approx(0.104304));
        REQUIRE(torque[5] == Approx(0.0114626));
    }

    SECTION("inverse dynamics 3")
    {
        Eigen::Vector<double, 6> position({ 0.17728, 0.314608, 0.717353, -0.12088, 0.84794, -0.203127 });
        Eigen::Vector<double, 6> velocity({ 0.368437, 0.821944, -0.0350187, -0.56835, 0.900505, 0.840257 });
        Eigen::Vector<double, 6> acceleration({ 0.762124, 0.282161, -0.136093, 0.239193, -0.437881, 0.572004 });

        Eigen::Vector<double, 6> torque = robot.getJointTorques(position, velocity, acceleration);

        REQUIRE(torque[0] == Approx(1.88672));
        REQUIRE(torque[1] == Approx(-25.9083));
        REQUIRE(torque[2] == Approx(-12.9013));
        REQUIRE(torque[3] == Approx(0.0445212));
        REQUIRE(torque[4] == Approx(-0.00248806));
        REQUIRE(torque[5] == Approx(0.0193007));
    }

    SECTION("inverse dynamics 4")
    {
        Eigen::Vector<double, 6> position({ -0.639255, -0.673737, -0.21662, 0.826053, 0.63939, -0.281809 });
        Eigen::Vector<double, 6> velocity({ 0.15886, -0.0948483, 0.374775, -0.80072, 0.061616, 0.514588 });
        Eigen::Vector<double, 6> acceleration({ 0.984457, 0.153942, 0.755228, 0.495619, 0.25782, -0.929158 });

        Eigen::Vector<double, 6> torque = robot.getJointTorques(position, velocity, acceleration);

        REQUIRE(torque[0] == Approx(2.4801));
        REQUIRE(torque[1] == Approx(41.6159));
        REQUIRE(torque[2] == Approx(13.2428));
        REQUIRE(torque[3] == Approx(0.342344));
        REQUIRE(torque[4] == Approx(0.302564));
        REQUIRE(torque[5] == Approx(0.00335514));
    }

    SECTION("inverse/forward dynamics")
    {
        for (unsigned i = 0; i < 10; ++i)
        {
            Eigen::Vector<double, 6> position = Eigen::Vector<double, 6>::Random();
            Eigen::Vector<double, 6> velocity = Eigen::Vector<double, 6>::Random();
            Eigen::Vector<double, 6> acceleration = Eigen::Vector<double, 6>::Random();

            Eigen::Vector<double, 6> torque =
              robot.getJointTorques(position, velocity, acceleration);

            Eigen::Vector<double, 6> acceleration_computed = robot.getJointAccelerations(position, velocity, torque);

            REQUIRE(acceleration[0] == Approx(acceleration_computed[0]));
            REQUIRE(acceleration[1] == Approx(acceleration_computed[1]));
            REQUIRE(acceleration[2] == Approx(acceleration_computed[2]));
            REQUIRE(acceleration[3] == Approx(acceleration_computed[3]));
            REQUIRE(acceleration[4] == Approx(acceleration_computed[4]));
            REQUIRE(acceleration[5] == Approx(acceleration_computed[5]));
        }
    }
}


TEST_CASE("UR5 from assets folder", "[UR5]")
{
    UR5<double> robot("../assets");
}

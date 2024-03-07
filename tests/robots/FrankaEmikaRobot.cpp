#include <catch.hpp>
#include <gafro/gafro.hpp>

using namespace gafro;

TEST_CASE("FrankaEmikaRobot", "[FrankaEmikaRobot]")
{
    FrankaEmikaRobot<double> robot;

    SECTION("Random configuration")
    {
        auto config = robot.getRandomConfiguration();

        REQUIRE(config.rows() == 7);
        REQUIRE(config.cols() == 1);
    }

    SECTION("Joint limits")
    {
        SECTION("Get min limits")
        {
            const Eigen::Matrix<double, 9, 1> &limitsMin = robot.getSystem().getJointLimitsMin();

            REQUIRE(limitsMin(0, 0) == Approx(-2.8973));
            REQUIRE(limitsMin(1, 0) == Approx(-1.7628));
            REQUIRE(limitsMin(2, 0) == Approx(-2.8973));
            REQUIRE(limitsMin(3, 0) == Approx(-3.0718));
            REQUIRE(limitsMin(4, 0) == Approx(-2.8973));
            REQUIRE(limitsMin(5, 0) == Approx(-0.0175));
            REQUIRE(limitsMin(6, 0) == Approx(-2.8973));
            REQUIRE(limitsMin(7, 0) == Approx(0.0));
            REQUIRE(limitsMin(8, 0) == Approx(0.0));
        }

        SECTION("Get max limits")
        {
            const Eigen::Matrix<double, 9, 1> &limitsMax = robot.getSystem().getJointLimitsMax();

            REQUIRE(limitsMax(0, 0) == Approx(2.8973));
            REQUIRE(limitsMax(1, 0) == Approx(1.7628));
            REQUIRE(limitsMax(2, 0) == Approx(2.8973));
            REQUIRE(limitsMax(3, 0) == Approx(-0.0698));
            REQUIRE(limitsMax(4, 0) == Approx(2.8973));
            REQUIRE(limitsMax(5, 0) == Approx(3.7525));
            REQUIRE(limitsMax(6, 0) == Approx(2.8973));
            REQUIRE(limitsMax(7, 0) == Approx(0.04));
            REQUIRE(limitsMax(8, 0) == Approx(0.04));
        }
    }

    SECTION("configuration 1")
    {
        Eigen::Vector<double, 7> configuration({ 0.5, -0.3, 0.0, -1.8, 0.0, 1.5, 1.0 });

        Motor<double> ee_motor = robot.getEEMotor(configuration);

        Point<double> point(0.0, 0.0, 0.0);

        Point<double> ee_point = ee_motor.apply(point);

        REQUIRE(ee_point.get<blades::e0>() == Approx(1.0));
        REQUIRE(ee_point.get<blades::e1>() == Approx(0.3954677774));
        REQUIRE(ee_point.get<blades::e2>() == Approx(0.2160450314));
        REQUIRE(ee_point.get<blades::e3>() == Approx(0.5583231694));
        REQUIRE(ee_point.get<blades::ei>() == Approx(0.25739749));
    }

    SECTION("configuration 2")
    {
        Eigen::Vector<double, 7> configuration({ -0.5, -0.3, 0.0, -1.8, 0.0, 1.5, 1.0 });

        Motor<double> ee_motor = robot.getEEMotor(configuration);

        Point<double> point(0.0, 0.0, 0.0);

        Point<double> ee_point = ee_motor.apply(point);

        REQUIRE(ee_point.get<blades::e0>() == Approx(1.0));
        REQUIRE(ee_point.get<blades::e1>() == Approx(0.3954677774));
        REQUIRE(ee_point.get<blades::e2>() == Approx(-0.2160450314));
        REQUIRE(ee_point.get<blades::e3>() == Approx(0.5583231694));
        REQUIRE(ee_point.get<blades::ei>() == Approx(0.25739749));
    }

    SECTION("inverse dynamics 1")
    {
        Eigen::Vector<double, 7> position({ 0.680375, -0.211234, 0.566198, 0.59688, 0.823295, -0.604897, -0.329554 });
        Eigen::Vector<double, 7> velocity({ 0.536459, -0.444451, 0.10794, -0.0452059, 0.257742, -0.270431, 0.0268018 });
        Eigen::Vector<double, 7> acceleration({ 0.904459, 0.83239, 0.271423, 0.434594, -0.716795, 0.213938, -0.967399 });

        Eigen::Vector<double, 7> torque =
          robot.getJointTorques(position, velocity, acceleration, 9.81, gafro::Wrench<double>({ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }));

        REQUIRE(torque[0] == Approx(0.982722));
        REQUIRE(torque[1] == Approx(17.4042));
        REQUIRE(torque[2] == Approx(1.11406));
        REQUIRE(torque[3] == Approx(-15.77));
        REQUIRE(torque[4] == Approx(-0.736949));
        REQUIRE(torque[5] == Approx(1.60781));
        REQUIRE(torque[6] == Approx(0.0118833));
    }

    SECTION("inverse dynamics 2")
    {
        Eigen::Vector<double, 7> position({ 0.997849, -0.563486, 0.0258648, 0.678224, 0.22528, -0.407937, 0.275105 });
        Eigen::Vector<double, 7> velocity({ 0.0485744, -0.012834, 0.94555, -0.414966, 0.542715, 0.05349, 0.539828 });
        Eigen::Vector<double, 7> acceleration({ -0.199543, 0.783059, -0.433371, -0.295083, 0.615449, 0.838053, -0.860489 });

        Eigen::Vector<double, 7> torque =
          robot.getJointTorques(position, velocity, acceleration, 9.81, gafro::Wrench<double>({ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }));

        REQUIRE(torque[0] == Approx(-0.75037));
        REQUIRE(torque[1] == Approx(31.4451));
        REQUIRE(torque[2] == Approx(-0.868337));
        REQUIRE(torque[3] == Approx(-18.6992));
        REQUIRE(torque[4] == Approx(-0.884175));
        REQUIRE(torque[5] == Approx(2.8628));
        REQUIRE(torque[6] == Approx(-0.0235222));
    }

    SECTION("inverse dynamics 3")
    {
        Eigen::Vector<double, 7> position({ 0.17728, 0.314608, 0.717353, -0.12088, 0.84794, -0.203127, 0.629534 });
        Eigen::Vector<double, 7> velocity({ 0.368437, 0.821944, -0.0350187, -0.56835, 0.900505, 0.840257, -0.70468 });
        Eigen::Vector<double, 7> acceleration({ 0.762124, 0.282161, -0.136093, 0.239193, -0.437881, 0.572004, -0.385084 });

        Eigen::Vector<double, 7> torque =
          robot.getJointTorques(position, velocity, acceleration, 9.81, gafro::Wrench<double>({ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }));

        REQUIRE(torque[0] == Approx(0.914278));
        REQUIRE(torque[1] == Approx(-17.4753));
        REQUIRE(torque[2] == Approx(1.51745));
        REQUIRE(torque[3] == Approx(1.16747));
        REQUIRE(torque[4] == Approx(0.675721));
        REQUIRE(torque[5] == Approx(1.59136));
        REQUIRE(torque[6] == Approx(0.00452535));
    }

    SECTION("inverse dynamics 4")
    {
        Eigen::Vector<double, 7> position({ -0.639255, -0.673737, -0.21662, 0.826053, 0.63939, -0.281809, 0.10497 });
        Eigen::Vector<double, 7> velocity({ 0.15886, -0.0948483, 0.374775, -0.80072, 0.061616, 0.514588, -0.39141 });
        Eigen::Vector<double, 7> acceleration({ 0.984457, 0.153942, 0.755228, 0.495619, 0.25782, -0.929158, 0.495606 });

        Eigen::Vector<double, 7> torque =
          robot.getJointTorques(position, velocity, acceleration, 9.81, gafro::Wrench<double>({ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }));

        REQUIRE(torque[0] == Approx(1.4954));
        REQUIRE(torque[1] == Approx(32.1859));
        REQUIRE(torque[2] == Approx(-1.63865));
        REQUIRE(torque[3] == Approx(-17.4762));
        REQUIRE(torque[4] == Approx(-1.35407));
        REQUIRE(torque[5] == Approx(1.99246));
        REQUIRE(torque[6] == Approx(-0.0101391));
    }

    SECTION("inverse/forward dynamics")
    {
        for (unsigned i = 0; i < 10; ++i)
        {
            Eigen::Vector<double, 7> position = Eigen::Vector<double, 7>::Random();
            Eigen::Vector<double, 7> velocity = Eigen::Vector<double, 7>::Random();
            Eigen::Vector<double, 7> acceleration = Eigen::Vector<double, 7>::Random();

            Eigen::Vector<double, 7> torque =
              robot.getJointTorques(position, velocity, acceleration, 9.81, gafro::Wrench<double>({ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }));

            Eigen::Vector<double, 7> acceleration_computed = robot.getJointAccelerations(position, velocity, torque);

            REQUIRE(acceleration[0] == Approx(acceleration_computed[0]));
            REQUIRE(acceleration[1] == Approx(acceleration_computed[1]));
            REQUIRE(acceleration[2] == Approx(acceleration_computed[2]));
            REQUIRE(acceleration[3] == Approx(acceleration_computed[3]));
            REQUIRE(acceleration[4] == Approx(acceleration_computed[4]));
            REQUIRE(acceleration[5] == Approx(acceleration_computed[5]));
            REQUIRE(acceleration[6] == Approx(acceleration_computed[6]));
        }
    }
}

TEST_CASE("FrankaEmikaRobot from assets folder", "[FrankaEmikaRobot]")
{
    FrankaEmikaRobot<double> robot("../assets");
}

-- phpMyAdmin SQL Dump
-- version 4.9.4
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Jun 13, 2020 at 08:13 PM
-- Server version: 10.2.31-MariaDB
-- PHP Version: 5.5.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `luuksiewers`
--

-- --------------------------------------------------------

--
-- Table structure for table `c_bedTimeRecords`
--

CREATE TABLE `c_bedTimeRecords` (
  `id` int(12) NOT NULL,
  `deviceId` int(12) NOT NULL,
  `inBedRecord` timestamp NULL DEFAULT NULL,
  `outBedRecord` timestamp NULL DEFAULT NULL,
  `inBedRecommended` timestamp NULL DEFAULT NULL,
  `outBedRecommended` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `c_bedTimeRecords`
--

INSERT INTO `c_bedTimeRecords` (`id`, `deviceId`, `inBedRecord`, `outBedRecord`, `inBedRecommended`, `outBedRecommended`) VALUES
(8, 1, '2020-06-06 21:10:46', '2020-06-07 09:33:21', '2020-06-06 20:30:00', '2020-06-07 08:15:00'),
(9, 1, '2020-06-07 21:40:32', '2020-06-08 09:01:21', '2020-06-07 20:20:00', '2020-06-08 08:15:00'),
(10, 1, '2020-06-08 21:55:11', '2020-06-09 07:21:21', '2020-06-08 20:25:00', '2020-06-09 08:20:00'),
(11, 1, '2020-06-09 21:59:11', '2020-06-10 07:24:12', '2020-06-09 20:30:00', '2020-06-10 08:25:00'),
(118, 1, '2020-06-05 21:23:21', '2020-06-06 08:21:34', '2020-06-05 20:40:00', '2020-06-06 08:10:00');

-- --------------------------------------------------------

--
-- Table structure for table `c_chronotypes`
--

CREATE TABLE `c_chronotypes` (
  `id` int(12) NOT NULL,
  `name` varchar(12) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `inBedTime` time NOT NULL,
  `outBedTime` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `c_chronotypes`
--

INSERT INTO `c_chronotypes` (`id`, `name`, `inBedTime`, `outBedTime`) VALUES
(5, 'bear', '23:00:00', '07:00:00'),
(6, 'dolphin', '22:30:00', '06:30:00'),
(7, 'lion', '22:00:00', '05:30:00'),
(8, 'wolf', '23:00:00', '07:00:00');

-- --------------------------------------------------------

--
-- Table structure for table `c_devices`
--

CREATE TABLE `c_devices` (
  `id` int(12) NOT NULL,
  `userId` int(12) DEFAULT NULL,
  `sunriseTime` time DEFAULT NULL,
  `sunsetTime` time DEFAULT NULL,
  `strictness` float NOT NULL DEFAULT 0.5
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `c_devices`
--

INSERT INTO `c_devices` (`id`, `userId`, `sunriseTime`, `sunsetTime`, `strictness`) VALUES
(1, 11, '09:45:45', '23:18:18', 0.66),
(2, NULL, NULL, NULL, 0.5),
(3, NULL, NULL, NULL, 0.44),
(4, NULL, NULL, NULL, 0.5);

-- --------------------------------------------------------

--
-- Table structure for table `c_users`
--

CREATE TABLE `c_users` (
  `id` int(11) NOT NULL,
  `firstName` varchar(30) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `birthdate` date NOT NULL,
  `email` varchar(75) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `password` varchar(75) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `chronotype` varchar(30) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `c_users`
--

INSERT INTO `c_users` (`id`, `firstName`, `birthdate`, `email`, `password`, `chronotype`) VALUES
(11, 'Luuk', '1998-03-30', 'luuk.siewers@student.hku.nl', 'hoi', 'bear');

-- --------------------------------------------------------

--
-- Table structure for table `products`
--

CREATE TABLE `products` (
  `id` int(11) NOT NULL,
  `location` varchar(30) NOT NULL,
  `userId` int(11) NOT NULL,
  `password` varchar(75) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `products`
--

INSERT INTO `products` (`id`, `location`, `userId`, `password`) VALUES
(1, 'Living room', 2, 'kaasje'),
(2, 'bedroom', 4, 'kaasislekker'),
(3, 'bathroom', 1, 'welveganhe'),
(4, 'backyard', 5, 'nogeenwachtwoordje'),
(5, 'bedroom', 3, 'indebadkamer'),
(6, 'living room', 6, 'leven=life'),
(7, 'bedroom', 7, 'lifeyourlive');

-- --------------------------------------------------------

--
-- Table structure for table `temperatures`
--

CREATE TABLE `temperatures` (
  `id` int(11) NOT NULL,
  `productId` int(11) NOT NULL,
  `celsius` int(3) NOT NULL,
  `dateTime` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `temperatures`
--

INSERT INTO `temperatures` (`id`, `productId`, `celsius`, `dateTime`) VALUES
(1, 1, 20, '2020-04-17 14:11:20'),
(2, 2, 21, '2020-04-23 11:03:35'),
(3, 4, 23, '2020-04-21 10:03:52'),
(4, 6, 14, '2020-04-24 04:04:07'),
(5, 2, 21, '2020-04-23 16:04:29'),
(6, 7, 16, '2020-04-19 05:04:46'),
(8, 4, 24, '2020-05-08 13:54:43'),
(9, 22, 2, '2020-05-08 14:25:51'),
(10, 1, 5, '2020-05-08 14:27:01'),
(12, 1, 20, '2020-05-12 14:24:11'),
(13, 1, 30, '2020-05-12 14:24:46');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `lastName` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `firstName` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `nickName` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `email` varchar(70) COLLATE utf8_unicode_ci NOT NULL,
  `password` varchar(75) COLLATE utf8_unicode_ci NOT NULL,
  `birthdate` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `lastName`, `firstName`, `nickName`, `email`, `password`, `birthdate`) VALUES
(1, 'Siewers', 'Luuk', 'lucky luke', 'luuk.siewers@student.hku.nl', 'wwvanluuk', '2017-05-02'),
(2, 'Korssen', 'Daniel', 'beepboop', 'daniel.korssen@student.hku.nl', 'wwvandaniel', '1997-11-10'),
(3, 'van Bentem', 'Noa', 'The OG', 'noah.vanbentem@student.hku.nl', 'wwvannoa\r\n', '1996-01-03'),
(4, 'Platjouw', 'Sjors', 'Vosje', 'sjors.platjouw@student.hku.nl', 'wwvansjors', '1996-03-05'),
(5, 'ter Pelle', 'Marijke ', 'whatthefontnot', 'marijke.terpelle@student.hku.nl', 'wwvanmarijke', '1997-11-05'),
(6, 'Sordam', 'Marciano', 'marciano.cs', 'marciano.sordam@student.hku.nl', 'wwvanmarciano', '1999-05-05'),
(7, 'Groothuis', 'Marieke', 'Dice', 'marieke.groothuis@student.hku.nl', 'wwvanmarieke', '1992-06-12');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `c_bedTimeRecords`
--
ALTER TABLE `c_bedTimeRecords`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `c_chronotypes`
--
ALTER TABLE `c_chronotypes`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `c_devices`
--
ALTER TABLE `c_devices`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `c_users`
--
ALTER TABLE `c_users`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `products`
--
ALTER TABLE `products`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `temperatures`
--
ALTER TABLE `temperatures`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `c_bedTimeRecords`
--
ALTER TABLE `c_bedTimeRecords`
  MODIFY `id` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=146;

--
-- AUTO_INCREMENT for table `c_chronotypes`
--
ALTER TABLE `c_chronotypes`
  MODIFY `id` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `c_devices`
--
ALTER TABLE `c_devices`
  MODIFY `id` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `c_users`
--
ALTER TABLE `c_users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT for table `products`
--
ALTER TABLE `products`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `temperatures`
--
ALTER TABLE `temperatures`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

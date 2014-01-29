-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jan 30, 2014 at 02:07 AM
-- Server version: 5.5.34
-- PHP Version: 5.3.10-1ubuntu3.9

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `distributed`
--

-- --------------------------------------------------------

--
-- Table structure for table `diff`
--

CREATE TABLE IF NOT EXISTS `diff` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(256) NOT NULL,
  `filename` varchar(256) NOT NULL,
  `filesame` varchar(256) NOT NULL,
  `finished` tinyint(1) NOT NULL,
  `percent` varchar(10) NOT NULL,
  `result` varchar(256) NOT NULL,
  `created` datetime DEFAULT NULL,
  `modified` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

--
-- Dumping data for table `diff`
--

INSERT INTO `diff` (`id`, `name`, `filename`, `filesame`, `finished`, `percent`, `result`, `created`, `modified`) VALUES
(1, 'reagentc.txt', '/var/www/cake/app/uploads/52e7a488-6160-46d3-9885-070dc0a83865', '/koppae/123123123', 1, '', 'AABVBASDXCZCXZXCASDADASDXZCZ', '2014-01-28 19:37:28', '2014-01-28 23:44:13'),
(2, 'pass.txt', '/var/www/cake/app/uploads/52e7bea3-0c2c-4b8d-9720-045ec0a83865', '/asdasd/asdasd/asfasf/asd', 1, '120', '/var/www/cake/app/result/SNV8pcsbla', '2014-01-28 21:28:51', '2014-01-29 20:17:19'),
(3, 'rearrange.c', '/var/www/cake/app/uploads/52e91acd-85d4-4149-bcc8-3e1dc0a83865', '', 0, '', '', '2014-01-29 22:14:21', '2014-01-29 22:14:21'),
(4, 'k.txt', '/var/www/cake/app/uploads/52e91ec4-6e7c-461d-b038-3b56c0a83865', '/test/filesame.txt', 1, '26', '/test/result_test.txt', '2014-01-29 22:31:16', '2014-01-29 22:31:16');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

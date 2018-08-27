/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "storage/cache/storage_cache_types.h"
#include "base/basic_types.h"
#include <crl/crl_object_on_queue.h>
#include <crl/crl_time.h>
#include <QtCore/QString>

namespace Storage {
class EncryptionKey;
namespace Cache {
namespace details {
class DatabaseObject;
} // namespace details

class Database {
public:
	using Settings = details::Settings;
	Database(const QString &path, const Settings &settings);

	void open(EncryptionKey key, FnMut<void(Error)> done = nullptr);
	void close(FnMut<void()> done = nullptr);

	void put(
		const Key &key,
		QByteArray value,
		FnMut<void(Error)> done = nullptr);
	void get(const Key &key, FnMut<void(QByteArray)> done);
	void remove(const Key &key, FnMut<void(Error)> done = nullptr);

	void putIfEmpty(
		const Key &key,
		QByteArray value,
		FnMut<void(Error)> done = nullptr);
	void copyIfEmpty(
		const Key &from,
		const Key &to,
		FnMut<void(Error)> done = nullptr);
	void moveIfEmpty(
		const Key &from,
		const Key &to,
		FnMut<void(Error)> done = nullptr);

	void clear(FnMut<void(Error)> done = nullptr);

	~Database();

private:
	using Implementation = details::DatabaseObject;
	crl::object_on_queue<Implementation> _wrapped;

};

} // namespace Cache
} // namespace Storage
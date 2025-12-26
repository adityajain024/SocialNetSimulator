SocialNet Simulator README

This program, SocialNet, is a command-line simulator modeling the
backend services for a social network. It is designed to demonstrate
proficiency with custom-built data structures: an undirected Graph for
managing user friendships and an AVL Tree for storing user posts.

Implementation Summary -

- Users and Friends: The network is represented as a Graph, where users
  are vertices and friendships are edges. User mapping is handled by a
  standard C++ unordered_map for case-insensitive lookup.

- Posts: Each user\'s posts are stored in a self-balancing AVL Tree. The
  posts are ordered primarily by their time of creation (most recent
  first) and secondarily by a unique post number to ensure efficient
  retrieval of recent content in O(logN) time.

- Case Sensitivity: All usernames and post contents are treated as
  case-insensitive. So whenever the program outputs a username or post
  content, it will be lowercase, and all the usernames and post content
  will be stored in lowercase format in the program.

Social Network Operations

- ADD_USER \[username\]

  - Normal: Prints a success message (e.g., Successfully added username
    to the network.).

  - Edge Case: If the user already exists, it prints: User already
    present.

- ADD_FRIEND \[username1\] \[username2\]

  - Normal: Prints: Added \[username1\] and \[username2\] as friends.

  - Edge Cases:

    - If a user doesn\'t exist: \[user\] doesn\'t exist.

    - If no input is given in place of the username: Error: Empty
      username given.

    - If they are already friends: Already friends.

    - If the usernames are identical: Please input 2 different users.

- LIST_FRIENDS \[username\]

  - Normal: Prints Listing friends of \[username\] followed by a
    numbered list of friends, sorted alphabetically.

  - Edge Cases:

    - If the user doesn\'t exist: User doesn\'t exist.

    - If no input is given in place of the username: Error: Empty
      username given.

    - If the user has no friends: User has no friends.

- SUGGEST_FRIENDS \[username\] \[N\]

  - Normal: Outputs a numbered list of up to N users who are \"friends
    of a friend\" but not direct friends. Recommendations are ranked by
    number of mutual friends (descending), with ties broken by
    alphabetical order (ascending).

  - Edge Cases:

    - If the user doesn\'t exist: User doesn\'t exist.

    - If no input is given in place of the username: Error: Empty
      username given.

    - If N\<=0: Please enter a number greater than 0.

    - If input given is not a valid number: Please enter valid number.

    - If there are no potential suggestions (user has no friends or
      candidates are all already friends): User has no possible
      suggestions. or User has no friends..

    - If fewer than N candidates exist, all available candidates are
      listed.

- DEGREES_OF_SEPARATION \[username1\] \[username2\]

  - Normal: Prints the length of the shortest path between the two users
    (e.g., Degrees of separation are 2.)

  - Edge Cases:

    - If the users are the same: Degrees of separation are 0.

    - If no path exists (they are not connected): Degrees of separation
      are -1.

    - If a user doesn\'t exist: \[User\] doesn\'t exist.

User Content Operations

- ADD_POST \[username\] \[post content\]

  - Normal: Prints: Added post successfully..

  - Edge Cases:

    - If the user doesn\'t exist: User doesn\'t exist.

    - If the post content is empty: Please enter non empty post content.

- OUTPUT_POSTS \[username\] \[N\]

  - Normal: Prints a numbered list of the most recent \$N\$ posts in
    reverse chronological order (most recent first).

  - Edge Cases:

    - If the user doesn\'t exist: User doesn\'t exist.

    - If the user has no posts: User has no posts.

    - If N=-1: All posts are outputted in reverse chronological order.

    - If N is greater than the total number of posts, all available
      posts are listed.

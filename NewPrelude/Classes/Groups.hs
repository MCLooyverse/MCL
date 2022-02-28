module Groups (
  Semigroup((<>)),
  Monoid(id),
  Group(inv)
  ) where

  import Prelude()



  infixl 6 <> -- Same as +
  -- | Any instance should satisfy:
  --
  -- [Associativity] @(a <> b) <> c = a <> (b <> c)@
  class Semigroup a where
    (<>) :: a -> a -> a

  -- | Any instance should satisfy:
  --
  -- [Right Identity] @a <> id = a@
  -- [Left Identity]  @id <> a = a@
  --
  -- In addition to the Semigroup rules.
  class Semigroup a => Monoid a where
    id :: a

  -- | Any instance should satisfy:
  --
  -- [Right Inverse] @a <> inv a = id@
  -- [Left Inverse]  @inv a <> a = id@
  --
  -- From this, it follows that @inv ∘ inv = id@
  class Monoid a => Group a where
    inv :: a -> a
